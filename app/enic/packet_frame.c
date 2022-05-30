
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "msg.h"
#include "inet.h"
#include "packet_frame.h"

typedef enum {
    s_eth_hdr,
    s_ip_hdr,
    s_esp_hdr,
    s_esp_iv,
    s_esp_payload,
    s_esp_trailer,
    s_esp_icv,
} stateTypeDef;

#define CURRENT_STATE()     state
#define UPDATE_STATE(STATE) state = (stateTypeDef) (STATE);
#define REDISSECT()         goto redissect;
#define RETURN(RET)         return(RET);

#define OFFSET(L)                                                              \
    do {                                                                       \
        frame->data    += (L);                                                 \
        frame->dataLen -= (L);                                                 \
    } while (0)

#if DEBUG
# define STRICT_CHECK(COND)                                                    \
    do {                                                                       \
        if (COND) {                                                            \
            printf("Frame Unknown: Invalid length/type\n");                    \
            RETURN(SECERR_INVAL);                                              \
        }                                                                      \
    } while (0)
#else
# define STRICT_CHECK(COND)
#endif

#define SUBSET_REMAINING(N, R)                                                 \
    ({                                                                         \
        STRICT_CHECK(N > frameTable->nents);                                   \
        frameTypeDef *__frame = &frameTable->frame[N];                         \
        __frame->reportedLen = R;                                              \
        __frame;                                                               \
    })

/* Offsets of fields within an IP header. */
#define IPH_V_HL            0
#define IPH_TOS             1
#define IPH_LEN             2
#define IPH_ID              4
#define IPH_OFF             6
#define IPH_TTL             8
#define IPH_P               9
#define IPH_SUM             10
#define IPH_SRC             12
#define IPH_DST             16

#define ETH_HEADER_SIZE     14
/* Minimum IP header length. */
#define IPH_MIN_LEN         20
#define ESP_HEADER_SIZE     8
#define ESP_IV_SIZE         8
#define ESP_TRAILER_SIZE    2
#define ESP_ICV_SIZE        16

#ifdef DEBUG
#ifndef ETHERTYPE_IP
#define ETHERTYPE_IP        0x0800
#endif
#ifndef ETHERTYPE_IPv6
#define ETHERTYPE_IPv6      0x86DD
#endif

/* IP protocol numbers. */
#define IP_PROTO_TCP        6       /* TCP - RFC792 */
#define IP_PROTO_UDP        17      /* user datagram protocol - RFC768 */
#define IP_PROTO_ESP        50      /* Encap Security Payload for IPv6 - RFC2406 */
#define IP_PROTO_UDPLITE    136     /* Lightweight user datagram protocol - RFC3828 */

typedef struct {
    uint32_t value;
    const uint8_t *strptr;
} Value_StringTypeDef;

typedef struct {
    uint8_t  ver;           /* 4 */
    uint8_t  tos;           /* type of service */
    uint32_t len;           /* total length */
    uint16_t id;            /* identification */
    uint16_t off;           /* fragment offset */
    uint8_t  ttl;           /* time-to-live */
    uint8_t  proto;         /* protocol */
    uint16_t sum;           /* checksum */
    AddressTypeDef src;     /* source address */
    AddressTypeDef dst;     /* destination address */
} IPv4_HDRTypeDef;

typedef struct {
    AddressTypeDef dst;
    AddressTypeDef src;
    uint16_t type;
} Eth_HDRTypeDef;

typedef struct {
    uint8_t *realData;
    uint32_t realDataLen;
} TVBuffTypeDef;

/*
 * If a user _does_ pass in a too-small buffer, this is probably
 * going to be too long to fit.  However, even a partial string
 * starting with "[Buf" should provide enough of a clue to be
 * useful.
 */
#define Return_IF_NoSpace(strLen, buf, bufLen)                                 \
    do {                                                                       \
        if ((strLen) > (bufLen)) {                                             \
            (void)strncpy(buf, "[Buffer too small]", bufLen);                  \
            return;                                                            \
        }                                                                      \
    } while (0)

static
const uint8_t bitMask8[] = {
    0x00,
    0x01,
    0x03,
    0x07,
    0x0f,
    0x1f,
    0x3f,
    0x7f,
    0xff
};

static
const char fastStrings[][4] = {
    "0", "1", "2", "3", "4", "5", "6", "7",
    "8", "9", "10", "11", "12", "13", "14", "15",
    "16", "17", "18", "19", "20", "21", "22", "23",
    "24", "25", "26", "27", "28", "29", "30", "31",
    "32", "33", "34", "35", "36", "37", "38", "39",
    "40", "41", "42", "43", "44", "45", "46", "47",
    "48", "49", "50", "51", "52", "53", "54", "55",
    "56", "57", "58", "59", "60", "61", "62", "63",
    "64", "65", "66", "67", "68", "69", "70", "71",
    "72", "73", "74", "75", "76", "77", "78", "79",
    "80", "81", "82", "83", "84", "85", "86", "87",
    "88", "89", "90", "91", "92", "93", "94", "95",
    "96", "97", "98", "99", "100", "101", "102", "103",
    "104", "105", "106", "107", "108", "109", "110", "111",
    "112", "113", "114", "115", "116", "117", "118", "119",
    "120", "121", "122", "123", "124", "125", "126", "127",
    "128", "129", "130", "131", "132", "133", "134", "135",
    "136", "137", "138", "139", "140", "141", "142", "143",
    "144", "145", "146", "147", "148", "149", "150", "151",
    "152", "153", "154", "155", "156", "157", "158", "159",
    "160", "161", "162", "163", "164", "165", "166", "167",
    "168", "169", "170", "171", "172", "173", "174", "175",
    "176", "177", "178", "179", "180", "181", "182", "183",
    "184", "185", "186", "187", "188", "189", "190", "191",
    "192", "193", "194", "195", "196", "197", "198", "199",
    "200", "201", "202", "203", "204", "205", "206", "207",
    "208", "209", "210", "211", "212", "213", "214", "215",
    "216", "217", "218", "219", "220", "221", "222", "223",
    "224", "225", "226", "227", "228", "229", "230", "231",
    "232", "233", "234", "235", "236", "237", "238", "239",
    "240", "241", "242", "243", "244", "245", "246", "247",
    "248", "249", "250", "251", "252", "253", "254", "255"
};

static
const Value_StringTypeDef IPProtoVals[] = {
    {IP_PROTO_TCP,      "TCP"                   },  /* [RFC793] */
    {IP_PROTO_ESP,      "Encap Security Payload"},  /* [RFC4303] */
    {0,                 NULL                    },
};

static
const Value_StringTypeDef EtypeVals[] = {
    {ETHERTYPE_IP,      "IPv4"},
    {ETHERTYPE_IPv6,    "IPv6"},
    {0,                 NULL  }
};

__STATIC_FORCEINLINE
const uint8_t *fastEnsureContiguous(TVBuffTypeDef *tvb,
                                    const int offset,
                                    const uint32_t length)
{
    uint32_t endOffset;
    uint32_t uOffset;

    uOffset = offset;
    endOffset = uOffset + length;

    if (__rv_likely(endOffset <= tvb->realDataLen)) {
        return tvb->realData + uOffset;
    }

    /* not reached */
    return NULL;
}

uint8_t TVB_Get_UINT8(TVBuffTypeDef *tvb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(tvb, offset, 1);
    return *ptr;
}

uint16_t TVB_Get_ntohs(TVBuffTypeDef *tvb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(tvb, offset, 2);
    return ntoh16(ptr);
}

uint32_t TVB_Get_ntohl(TVBuffTypeDef *tvb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(tvb, offset, 4);
    return ntoh32(ptr);
}

uint64_t TVB_Get_ntoh64(TVBuffTypeDef *tvb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(tvb, offset, 8);
    return ntoh64(ptr);
}

uint64_t TVB_Get_Bits64(TVBuffTypeDef *tvb,
                        uint32_t bitOffset,
                        const int32_t Total_No_Of_Bits)
{
    uint64_t value;
    uint32_t octetOffset = bitOffset >> 3;
    uint8_t  Required_Bits_In_First_Octet = 8 - (bitOffset % 8);

    if (Required_Bits_In_First_Octet > Total_No_Of_Bits) {
        /* the required bits don't extend to the end of the first octet */
        uint8_t rightShift = Required_Bits_In_First_Octet - Total_No_Of_Bits;
        value = (TVB_Get_UINT8(tvb, octetOffset) >> rightShift) & bitMask8[Total_No_Of_Bits % 8];
    } else {
        uint8_t remainingBitLength = Total_No_Of_Bits;

        /* get the bits up to the first octet boundary */
        value = 0;
        Required_Bits_In_First_Octet %= 8;
        if (Required_Bits_In_First_Octet != 0) {
            value = TVB_Get_UINT8(tvb, octetOffset) & bitMask8[Required_Bits_In_First_Octet];
            remainingBitLength -= Required_Bits_In_First_Octet;
            octetOffset++;
        }
        /* take the biggest words, shorts or octets that we can */
        while (remainingBitLength > 7) {
            switch (remainingBitLength >> 4) {
            case 0:
                /* 8 - 15 bits. (note that 0 - 7 would have dropped out of the while() loop) */
                value <<= 8;
                value += TVB_Get_UINT8(tvb, octetOffset);
                remainingBitLength -= 8;
                octetOffset++;
                break;

            case 1:
                /* 16 - 31 bits */
                value <<= 16;
                value += TVB_Get_ntohs(tvb, octetOffset);
                remainingBitLength -= 16;
                octetOffset += 2;
                break;

            case 2:
            case 3:
                /* 32 - 63 bits */
                value <<= 32;
                value += TVB_Get_ntohl(tvb, octetOffset);
                remainingBitLength -= 32;
                octetOffset += 4;
                break;

            default:
                /* 64 bits (or more???) */
                value = TVB_Get_ntoh64(tvb, octetOffset);
                remainingBitLength -= 64;
                octetOffset += 8;
                break;
            }
        }
        /* get bits from any partial octet at the tail */
        if (remainingBitLength) {
            value <<= remainingBitLength;
            value += (TVB_Get_UINT8(tvb, octetOffset) >> (8 - remainingBitLength));
        }
    }

    return value;
}

/* Get 1 - 8 bits */
uint8_t TVB_Get_Bits8(TVBuffTypeDef *tvb,
                      uint32_t bitOffset,
                      const int32_t No_Of_Bits)
{
    return (uint8_t)TVB_Get_Bits64(tvb, bitOffset, No_Of_Bits);
}

const uint8_t *
Try_Val_TO_StrIdx(const uint32_t val,
                  const Value_StringTypeDef *vs,
                  int32_t *idx)
{
    int32_t i = 0;

    if (vs) {
        while (vs[i].strptr) {
            if (vs[i].value == val) {
                *idx = i;
                return (vs[i].strptr);
            }
            i++;
        }
    }

    *idx = -1;
    return NULL;
}

const uint8_t *
Try_Val_TOStr(const uint32_t val,
              const Value_StringTypeDef *vs)
{
    int32_t ignore_me;
    return Try_Val_TO_StrIdx(val, vs, &ignore_me);
}

const uint8_t *
Val_To_StrConst(const uint32_t val,
                const Value_StringTypeDef *vs,
                const char *unknownStr)
{
    const uint8_t *ret;

    ret = Try_Val_TOStr(val, vs);
    if (ret != NULL)
        return ret;

    return unknownStr;
}

__STATIC_FORCEINLINE
char Low_Nibble_Of_Octet_ToHex(uint8_t oct)
{
    /* At least one version of Apple's C compiler/linker is buggy, causing
       a complaint from the linker about the "literal C string section"
       not ending with '\0' if we initialize a 16-element "char" array with
       a 16-character string, the fact that initializing such an array with
       such a string is perfectly legitimate ANSI C nonwithstanding, the 17th
       '\0' byte in the string nonwithstanding. */
    static const uint8_t hex_digits[16] = {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };

    return hex_digits[oct & 0xF];
}

__STATIC_FORCEINLINE
char *Byte_ToHex(char *out, uint32_t dword)
{
    *out++ = Low_Nibble_Of_Octet_ToHex(dword >> 4);
    *out++ = Low_Nibble_Of_Octet_ToHex(dword);
    return out;
}

char *Bytes_To_Hexstr_Punct(char *out,
                            const uint8_t *ad,
                            uint32_t len,
                            char punct)
{
    uint32_t i;

    out = Byte_ToHex(out, ad[0]);
    for (i = 1; i < len; i++) {
        *out++ = punct;
        out = Byte_ToHex(out, ad[i]);
    }
    return out;
}

/*
   This function is very fast and this function is called a lot.
   XXX update the address_to_str stuff to use this function.
   */
void IP_To_STR_Buf(const uint8_t *ad, uint8_t *buf, const int buf_len)
{
    register uint8_t const *p;
    register uint8_t *b = buf;

    Return_IF_NoSpace(16, buf, buf_len);

    p = fastStrings[*ad++];
    do {
        *b++ = *p;
        p++;
    } while (*p);
    *b++ = '.';

    p = fastStrings[*ad++];
    do {
        *b++ = *p;
        p++;
    } while (*p);
    *b++ = '.';

    p = fastStrings[*ad++];
    do {
        *b++ = *p;
        p++;
    } while (*p);
    *b++ = '.';

    p = fastStrings[*ad];
    do {
        *b++ = *p;
        p++;
    } while (*p);
    *b = 0;
}

const uint8_t *IPV4_TOStr(const AddressTypeDef *addr,
                          uint8_t *buf, int bufLen)
{
    IP_To_STR_Buf((const uint8_t *)addr->data, buf, bufLen);
    return buf;
}

const uint8_t *Ether_TOStr(const AddressTypeDef *addr,
                           uint8_t *buf, int bufLen)
{
    Bytes_To_Hexstr_Punct(buf, (const uint8_t *)addr->data, 6, ':');
    buf[17] = '\0';
    return buf;
}

char *
Decode_Bits_IN_Field(const uint32_t bit_offset,
                     const int no_of_bits,
                     const uint64_t value)
{
    uint64_t mask;
    static char str[256 + 64]; /* static, May overflow */
    int bit, str_p = 0;
    int i;
    int max_bits = Min(64, no_of_bits);

    mask = 1ULL << (max_bits - 1);

    memset(str, 0, sizeof(str));
    /* Prepare the string, 256 pos for the bits and zero termination, + 64 for the spaces */
    for (bit = 0; bit < ((int)(bit_offset & 0x07)); bit++) {
        if (bit && (!(bit % 4))) {
            str[str_p] = ' ';
            str_p++;
        }
        str[str_p] = '.';
        str_p++;
    }

    /* read the bits for the int */
    for (i = 0; i < max_bits; i++) {
        if (bit && (!(bit % 4))) {
            str[str_p] = ' ';
            str_p++;
        }
        if (bit && (!(bit % 8))) {
            str[str_p] = ' ';
            str_p++;
        }
        bit++;
        if ((value & mask) != 0) {
            str[str_p] = '1';
            str_p++;
        } else {
            str[str_p] = '0';
            str_p++;
        }
        mask = mask >> 1;
    }

    for (; bit % 8; bit++) {
        if (bit && (!(bit % 4))) {
            str[str_p] = ' ';
            str_p++;
        }
        str[str_p] = '.';
        str_p++;
    }
    return str;
}

char *
Add_Bits_Format_Value(TVBuffTypeDef *tvb,
                      const uint32_t bit_offset,
                      const uint32_t no_of_bits,
                      char *value_str)
{
    char     *str = NULL;
    uint64_t value = 0;

    if (no_of_bits == 0) {
        printf("has a bit width of 0\n");
    }

    if (no_of_bits < 65) {
        value = TVB_Get_Bits64(tvb, bit_offset, no_of_bits);
    } else {
        printf("has a bit width of %u > 65", no_of_bits);
        return NULL;
    }

    str = Decode_Bits_IN_Field(bit_offset, no_of_bits, value);
    strcat(str, value_str);

    return str;
}

const char *
UINT_Bits_Format_Value(TVBuffTypeDef *tvb,
                       const uint32_t bit_offset,
                       const uint32_t no_of_bits,
                       const char *format, ...)
{
    va_list ap;
    static char dst[128];           /* static, May overflow */

    memset(dst, 0, sizeof(dst));

    va_start(ap, format);
    vsnprintf(dst, sizeof(dst), format, ap);
    va_end(ap);

    return Add_Bits_Format_Value(tvb, bit_offset, no_of_bits, dst);
}

static void Print_Frame_ESP(frameTableTypeDef *frameTable)
{
    return;
}

static void Print_Frame_IPv4(frameTableTypeDef *frameTable)
{
    uint8_t src[32];
    uint8_t dst[32];
    uint32_t hLen, optLen;

    TVBuffTypeDef tvb;
    IPv4_HDRTypeDef ipHDR;

    tvb.realData    = frameTable->frame[0].ip.hdr;
    tvb.realDataLen = frameTable->frame[0].ip.hdrLen;

    ipHDR.ver = TVB_Get_Bits8(&tvb, 0, 4);
    hLen = TVB_Get_Bits8(&tvb, 4, 4) * 4;  /* IP header length, in bytes */
    if ((hLen < IPH_MIN_LEN)) {
        printf("Bogus IP header length (%u, must be at least %u)",
               hLen, IPH_MIN_LEN);
        return;
    }

    ipHDR.tos   = TVB_Get_UINT8(&tvb, IPH_TOS);
    ipHDR.len   = TVB_Get_ntohs(&tvb, IPH_LEN);
    ipHDR.id    = TVB_Get_ntohs(&tvb, IPH_ID);
    ipHDR.off   = TVB_Get_ntohs(&tvb, IPH_OFF);
    ipHDR.ttl   = TVB_Get_UINT8(&tvb, IPH_TTL);
    ipHDR.proto = TVB_Get_UINT8(&tvb, IPH_P);
    ipHDR.sum   = TVB_Get_ntohs(&tvb, IPH_SUM);
    setAddress(&ipHDR.src, AT_IPv4, 4, fastEnsureContiguous(&tvb, IPH_SRC, 4));
    setAddress(&ipHDR.dst, AT_IPv4, 4, fastEnsureContiguous(&tvb, IPH_DST, 4));

    printf("    Internet Protocol Version %u, Src: %s, Dst: %s\n",
           ipHDR.ver,
           IPV4_TOStr(&ipHDR.src, src, sizeof(src)),
           IPV4_TOStr(&ipHDR.dst, dst, sizeof(dst)));
    printf("      %s\n",
           UINT_Bits_Format_Value(&tvb, 0, 4, " = Version: %u", ipHDR.ver));
    printf("      %s\n",
           UINT_Bits_Format_Value(&tvb, 4, 4,
                                  " = Header Length: %u bytes (%u)",
                                  hLen, hLen >> 2));
    printf("      Differentiated Services Field: 0x%02x\n"
           "      Total Length: %u\n"
           "      Identification: 0x%04x (%u)\n"
           "      Flags: 0x%04x\n"
           "      Time to live: %u\n"
           "      Protocol: %s (%u)\n"
           "      Header checksum: 0x%04x\n"
           "      Source: %s\n"
           "      Destination: %s\n",
           ipHDR.tos,
           ipHDR.len,
           ipHDR.id, ipHDR.id,
           ipHDR.off,
           ipHDR.ttl,
           Val_To_StrConst(ipHDR.proto, IPProtoVals, "Unknown"), ipHDR.proto,
           ipHDR.sum,
           IPV4_TOStr(&ipHDR.src, src, sizeof(src)),
           IPV4_TOStr(&ipHDR.dst, dst, sizeof(dst)));

    return;
}

static void Print_Frame_IPv6(frameTableTypeDef *frameTable)
{
    return;
}

static void Print_Frame_IP(frameTableTypeDef *frameTable)
{
    switch (Frame_IP_Ver(frameTable)) {
    case 4:
        Print_Frame_IPv4(frameTable);
        break;
    case 6:
        Print_Frame_IPv6(frameTable);
        break;
    default:
        printf("Bogus IP version\n");
        break;
    }

    return;
}

static void Print_Frame_Eth(frameTableTypeDef *frameTable)
{
    uint8_t src[32];
    uint8_t dst[32];

    TVBuffTypeDef tvb;
    Eth_HDRTypeDef eHDR;

    tvb.realData    = frameTable->frame[0].eth.hdr;
    tvb.realDataLen = frameTable->frame[0].eth.hdrLen;

    setAddress(&eHDR.dst, AT_ETHER, 6, fastEnsureContiguous(&tvb, 0, 6));
    setAddress(&eHDR.src, AT_ETHER, 6, fastEnsureContiguous(&tvb, 6, 6));
    eHDR.type = TVB_Get_ntohs(&tvb, 12);

    printf("    Ethernet II, Src: %s, Dst: %s\n"
           "      Type: %s (0x%04x)\n",
           Ether_TOStr(&eHDR.src, src, sizeof(src)),
           Ether_TOStr(&eHDR.dst, dst, sizeof(dst)),
           Val_To_StrConst(eHDR.type, EtypeVals, "Unknown"), eHDR.type);
    return;
}

static void Print_Frame(frameTableTypeDef *frameTable)
{
    printf("  Frame: %u bytes on wire \n", frameTable->containedLen);

    Print_Frame_Eth(frameTable);
    Print_Frame_IP(frameTable);
    Print_Frame_ESP(frameTable);
    return;
}
#else
__STATIC_FORCEINLINE
void Print_Frame(frameTableTypeDef *frameTable)
{
    return;
}
#endif

int Dissect_Frame(frameTableTypeDef *frameTable)
{
    int nents = 0;
    frameTypeDef *frame;
    stateTypeDef state = s_eth_hdr;

    frame = SUBSET_REMAINING(nents++, 0);

redissect:
    switch (CURRENT_STATE()) {
    case s_eth_hdr:
        frame->eth.hdr    = frame->data;
        frame->eth.hdrLen = ETH_HEADER_SIZE;
        OFFSET(ETH_HEADER_SIZE);

    case s_ip_hdr:
        switch (*(frame->data) >> 4) {
        case 4:
            frame->ip.hdr    = frame->data;
            frame->ip.hdrLen = IPH_MIN_LEN;
            OFFSET(IPH_MIN_LEN);
            break;
        case 6:
            break;
        default:
            printf("Bogus IP version\n");
            RETURN(SECERR_INVAL);
        }

    case s_esp_hdr:
        frame->esp.hdr    = frame->data;
        frame->esp.hdrLen = ESP_HEADER_SIZE;
        OFFSET(ESP_HEADER_SIZE);

    case s_esp_iv:
        frame->esp.iv    = frame->data;
        frame->esp.ivLen = ESP_IV_SIZE;
        OFFSET(ESP_IV_SIZE);
        frame->reportedLen = frameTable->containedLen -
                             frame->eth.hdrLen -
                             frame->ip.hdrLen -
                             frame->esp.hdrLen -
                             frame->esp.ivLen -
                             ESP_TRAILER_SIZE -
                             ESP_ICV_SIZE;
        UPDATE_STATE(s_esp_payload);

    case s_esp_payload:
        if (frame->dataLen < frame->reportedLen) {
            frame->esp.payload    = frame->data;
            frame->esp.payloadLen = frame->dataLen;
            frame = SUBSET_REMAINING(nents++,
                                     frame->reportedLen - frame->dataLen);
            REDISSECT();
        } else {
            STRICT_CHECK(frame->dataLen < frame->reportedLen);
            frame->esp.payload    = frame->data;
            frame->esp.payloadLen = frame->dataLen;
            OFFSET(frame->esp.payloadLen);
            frame->reportedLen = ESP_TRAILER_SIZE;
            UPDATE_STATE(s_esp_trailer);
        }

    case s_esp_trailer:
        if (frame->dataLen < frame->reportedLen) {
            frame->esp.trailer    = frame->data;
            frame->esp.trailerLen = frame->dataLen;
            frame = SUBSET_REMAINING(nents++,
                                     frame->reportedLen - frame->dataLen);
            REDISSECT();
        } else {
            STRICT_CHECK(frame->dataLen < frame->reportedLen);
            frame->esp.trailer    = frame->data;
            frame->esp.trailerLen = frame->dataLen;
            OFFSET(frame->esp.trailerLen);
            frame->reportedLen = ESP_ICV_SIZE;
            UPDATE_STATE(s_esp_icv);
        }

    case s_esp_icv:
        if (frame->dataLen < frame->reportedLen) {
            frame->esp.icv    = frame->data;
            frame->esp.icvLen = frame->dataLen;
            frame = SUBSET_REMAINING(nents++,
                                     frame->reportedLen - frame->dataLen);
            REDISSECT();
        } else {
            STRICT_CHECK(frame->dataLen < frame->reportedLen);
            frame->esp.icv    = frame->data;
            frame->esp.icvLen = frame->dataLen;
        }

    default:
        break;
    }

    Print_Frame(frameTable);
    return SECERR_OK;
}

