-
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "msg.h"
#include "inet.h"
#include "frame.h"
#define MSG_HEADER sizeof(uint64_t)
#ifdef DEBUG
int IP_Try_Dissect(skbufTypeDef *skb, Packet_InfoTypeDef *pinfo);

#ifndef ETHERTYPE_IP
#define ETHERTYPE_IP        0x0800
#endif
#ifndef ETHERTYPE_IPv6
#define ETHERTYPE_IPv6      0x86DD
#endif

/* TCP flags */
#define TH_FIN  0x0001
#define TH_SYN  0x0002
#define TH_RST  0x0004
#define TH_PUSH 0x0008
#define TH_ACK  0x0010
#define TH_URG  0x0020
#define TH_ECN  0x0040
#define TH_CWR  0x0080
#define TH_NS   0x0100
#define TH_RES  0x0E00 /* 3 reserved bits */
#define TH_MASK 0x0FFF

#define hi_nibble(b) (((b) & 0xf0) >> 4)
#define lo_nibble(b) ((b) & 0x0f)

typedef struct {
    uint32_t value;
    const uint8_t *strptr;
} Value_StringTypeDef;

/* the tcp header structure, passed to tap listeners */
typedef struct {
    uint16_t thSport;
    uint16_t thDport;
    uint32_t thSeq;
    uint32_t thACK;
    uint8_t  thHLen;
    uint16_t thFlags;
    uint32_t thWin;
    uint16_t thSum;
    uint16_t thURP;
} TCP_HDRTypeDef;

typedef struct {
    uint8_t  ipVer;         /* 4 */
    uint8_t  ipTOS;         /* type of service */
    uint32_t ipLen;         /* total length */
    uint16_t ipID;          /* identification */
    uint16_t ipOff;         /* fragment offset */
    uint8_t  ipTTL;         /* time-to-live */
    uint8_t  ipProto;       /* protocol */
    uint16_t ipSum;         /* checksum */
    AddressTypeDef ipSrc;   /* source address */
    AddressTypeDef ipDst;   /* destination address */
} IPv4_HDRTypeDef;

typedef struct {
    AddressTypeDef dst;
    AddressTypeDef src;
    uint16_t type;
} Eth_HDRTypeDef;

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
            return;                                                     \
        }                                                                      \
    } while (0)

static const char fastStrings[][4] = {
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
const Value_StringTypeDef EtypeVals[] = {
    {ETHERTYPE_IP,      "IPv4"},
    {ETHERTYPE_IPv6,    "IPv6"},
    {0,                 NULL  }
};

static
const Value_StringTypeDef IPProtoVals[] = {
    {IP_PROTO_TCP,      "TCP"                   },  /* [RFC793] */
    {IP_PROTO_ESP,      "Encap Security Payload"},  /* [RFC4303] */
    {0,                 NULL                    },
};

const uint8_t *fastEnsureContiguous(skbufTypeDef *skb,
                                    const int offset,
                                    const uint32_t length)
{
    uint32_t endOffset;
    uint32_t uOffset;

    uOffset = offset;
    endOffset = uOffset + length;

    if (endOffset <= skb->realDataLen) {
        return skb->realData + uOffset;
    }

    /* not reached */
    return NULL;
}

/**
 * * LFENCE used to serialize code execution (no OOO)
 * * Load buffers get are empty after lfence, no deliberate restrictions put on store buffers
 * */
uint64_t rdtsc_start(void)
{
    uint32_t cycles_high;
    uint32_t cycles_low;

    asm volatile("lfence\n\t"
            "rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            : "=r" (cycles_high), "=r" (cycles_low)
            : : "%rax", "%rdx", "%rcx");
    return (((uint64_t)cycles_high << 32) | cycles_low);
}


uint64_t rdtsc_end(void)
{
    uint32_t cycles_high;
    uint32_t cycles_low;

    asm volatile("rdtscp\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "lfence\n\t"
            : "=r" (cycles_high), "=r" (cycles_low)
            : : "%rax", "%rdx", "%rcx");

    return (((uint64_t)cycles_high << 32) | cycles_low);
}

size_t sg_copy_buffer(struct scatterlist *sgl, unsigned int nents, void *buf,
		      size_t buflen, off_t skip, bool to_buffer)
{
	unsigned int offset = 0;
	struct sg_mapping_iter miter;
	unsigned int sg_flags = SG_MITER_ATOMIC;
#if 0
	if (to_buffer)
		sg_flags |= SG_MITER_FROM_SG;
	else
		sg_flags |= SG_MITER_TO_SG;

	sg_miter_start(&miter, sgl, nents, sg_flags);

	if (!sg_miter_skip(&miter, skip))
		return false;

	while ((offset < buflen) && sg_miter_next(&miter)) {
		unsigned int len;

		len = min(miter.length, buflen - offset);

		if (to_buffer)
			memcpy(buf + offset, miter.addr, len);
		else
			memcpy(miter.addr, buf + offset, len);

		offset += len;
	}

	sg_miter_stop(&miter);
#endif
	return offset;
}

uint8_t Get_UINT8(skbufTypeDef *skb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(skb, offset, 1);
    return *ptr;
}

uint16_t Get_ntohs(skbufTypeDef *skb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(skb, offset, 2);
    return ntoh16(ptr);
}

uint32_t Get_ntohl(skbufTypeDef *skb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(skb, offset, 4);
    return ntoh32(ptr);
}

uint64_t Get_ntoh64(skbufTypeDef *skb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(skb, offset, 8);
    return ntoh64(ptr);
}

uint64_t Get_Bits64(skbufTypeDef *skb,
                    uint32_t bitOffset,
                    const int32_t Total_No_Of_Bits)
{
    uint64_t value;
    uint32_t octetOffset = bitOffset >> 3;
    uint8_t  Required_Bits_In_First_Octet = 8 - (bitOffset % 8);

    if (Required_Bits_In_First_Octet > Total_No_Of_Bits) {
        /* the required bits don't extend to the end of the first octet */
        uint8_t rightShift = Required_Bits_In_First_Octet - Total_No_Of_Bits;
        value = (Get_UINT8(skb, octetOffset) >> rightShift) & bitMask8[Total_No_Of_Bits % 8];
    } else {
        uint8_t remainingBitLength = Total_No_Of_Bits;

        /* get the bits up to the first octet boundary */
        value = 0;
        Required_Bits_In_First_Octet %= 8;
        if (Required_Bits_In_First_Octet != 0) {
            value = Get_UINT8(skb, octetOffset) & bitMask8[Required_Bits_In_First_Octet];
            remainingBitLength -= Required_Bits_In_First_Octet;
            octetOffset++;
        }
        /* take the biggest words, shorts or octets that we can */
        while (remainingBitLength > 7) {
            switch (remainingBitLength >> 4) {
            case 0:
                /* 8 - 15 bits. (note that 0 - 7 would have dropped out of the while() loop) */
                value <<= 8;
                value += Get_UINT8(skb, octetOffset);
                remainingBitLength -= 8;
                octetOffset++;
                break;

            case 1:
                /* 16 - 31 bits */
                value <<= 16;
                value += Get_ntohs(skb, octetOffset);
                remainingBitLength -= 16;
                octetOffset += 2;
                break;

            case 2:
            case 3:
                /* 32 - 63 bits */
                value <<= 32;
                value += Get_ntohl(skb, octetOffset);
                remainingBitLength -= 32;
                octetOffset += 4;
                break;

            default:
                /* 64 bits (or more???) */
                value = Get_ntoh64(skb, octetOffset);
                remainingBitLength -= 64;
                octetOffset += 8;
                break;
            }
        }
        /* get bits from any partial octet at the tail */
        if (remainingBitLength) {
            value <<= remainingBitLength;
            value += (Get_UINT8(skb, octetOffset) >> (8 - remainingBitLength));
        }
    }

    return value;
}

/* Get 1 - 8 bits */
uint8_t Get_Bits8(skbufTypeDef *skb,
                  uint32_t bitOffset,
                  const int32_t No_Of_Bits)
{
    return (uint8_t)Get_Bits64(skb, bitOffset, No_Of_Bits);
}

const uint8_t *Try_Val_TO_StrIdx(const uint32_t val,
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

const uint8_t *Ethernet_TOStr(const AddressTypeDef *addr,
                              uint8_t *buf, int bufLen)
{
    Bytes_To_Hexstr_Punct(buf, (const uint8_t *)addr->data, 6, ':');
    buf[17] = '\0';
    return buf;
}

/*
   This function is very fast and this function is called a lot.
   XXX update the address_to_str stuff to use this function.
   */
void
IP_To_STR_Buf(const uint8_t *ad, uint8_t *buf, const int buf_len)
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
Add_Bits_Format_Value(skbufTypeDef *skb,
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
        value = Get_Bits64(skb, bit_offset, no_of_bits);
    } else {
        printf("has a bit width of %u > 65", no_of_bits);
        return NULL;
    }

    str = Decode_Bits_IN_Field(bit_offset, no_of_bits, value);
    strcat(str, value_str);

    return str;
}

const char *
UINT_Bits_Format_Value(skbufTypeDef *skb,
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

    return Add_Bits_Format_Value(skb, bit_offset, no_of_bits, dst);
}

#if 0
int Dissect_ESP(frameTableTypeDef *frameTable)
{
    int ret = SECERR_OK;
    /* get esp info */
    pinfo->espBufLen      = skb->realDataLen;
    pinfo->espHdrLen      = 8;
    pinfo->espIVLen       = 8;
    pinfo->espTrailerLen  = 2;
    /* The ICV consists solely of the AES-GCM Authentication Tag.
    Implementations MUST support a full-length 16-octet ICV, and MAY
    support 8 or 12 octet ICVs, and MUST NOT support other ICV lengths. */
    pinfo->espICVLen      = 16;
    pinfo->espPayloadLen  = pinfo->espBufLen -
                            pinfo->espHdrLen -
                            pinfo->espIVLen -
                            pinfo->espICVLen;
    pinfo->espBuf         = skb->realData;
    pinfo->espHdr         = pinfo->espBuf;
    pinfo->espIV          = pinfo->espHdr + pinfo->espHdrLen;
    pinfo->espPayload     = pinfo->espBuf +
                            pinfo->espHdrLen +
                            pinfo->espIVLen;
    pinfo->espTrailer     = pinfo->espBuf +
                            pinfo->espHdrLen +
                            pinfo->espIVLen +
                            (pinfo->espPayloadLen - pinfo->espTrailerLen);
    pinfo->espICV         = pinfo->espBuf +
                            pinfo->espHdrLen +
                            pinfo->espIVLen +
                            pinfo->espPayloadLen;

    switch (pinfo->direction) {
    case INBOUND: {
        uint32_t spi = 0;
        uint32_t sequenceNumber;

        spi                   = ntoh32(pinfo->espHdr);
        sequenceNumber        = ntoh32(pinfo->espHdr + 4);

        printf("    Encapsulating Security Payload \n"
               "      ESP SPI: 0x%08x (%u) \n"
               "      ESP Sequence: %u \n",
               spi, spi,
               sequenceNumber);
    }
    break;
    case OUTBOUND: {
        uint64_t iv;
        uint32_t spi = 0;
        uint32_t sequenceNumber;
        uint8_t esp_Pad_Len;
        uint8_t encapsulated_Protocol;

        spi                   = ntoh32(pinfo->espHdr);
        sequenceNumber        = ntoh32(pinfo->espHdr + 4);
        iv                    = ntoh64(pinfo->espIV);
        esp_Pad_Len           = *pinfo->espTrailer;
        encapsulated_Protocol = *(pinfo->espTrailer + 1);

        printf("    Encapsulating Security Payload \n"
               "      ESP SPI: 0x%08x (%u) \n"
               "      ESP Sequence: %u \n"
               "      ESP IV: %016lx \n"
               "      ESP Pad Length: %u \n"
               "      Next header: %s (0x%02x) \n",
               spi, spi,
               sequenceNumber,
               iv,
               esp_Pad_Len,
               Val_To_StrConst(encapsulated_Protocol, IPProtoVals, "Unknown"),
               encapsulated_Protocol);

        pinfo->ipProto   = encapsulated_Protocol; /* get Next Header */
        skb->realData    = pinfo->espPayload;
        skb->realDataLen = pinfo->espPayloadLen -
                           esp_Pad_Len -
                           pinfo->espTrailerLen;

        ret = IP_Try_Dissect(skb, pinfo);
    }
    break;
    }

    return ret;
}
#endif
#if 0
__STATIC_FORCEINLINE
int Dissect_ESP(frameTableTypeDef *frameTable)
{
#if 0
    /* get esp info */
    pinfo->espBufLen     = skb->dataLen - pinfo->ethLen - pinfo->ipLen;
    pinfo->espHdrLen     = 8;
    pinfo->espIVLen      = 8;
    pinfo->espTrailerLen = 2;
    /* The ICV consists solely of the AES-GCM Authentication Tag.
    Implementations MUST support a full-length 16-octet ICV, and MAY
    support 8 or 12 octet ICVs, and MUST NOT support other ICV lengths. */
    pinfo->espICVLen     = 16;
    pinfo->espPayloadLen = pinfo->espBufLen -
                           pinfo->espHdrLen -
                           pinfo->espIVLen -
                           pinfo->espICVLen;
    pinfo->espBuf        = skb->data    + pinfo->ethLen + pinfo->ipLen;
    pinfo->espHdr        = pinfo->espBuf;
    pinfo->espIV         = pinfo->espHdr + pinfo->espHdrLen;
    pinfo->espPayload    = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen;
    pinfo->espTrailer    = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen +
                           (pinfo->espPayloadLen - pinfo->espTrailerLen);
    pinfo->espICV        = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen +
                           pinfo->espPayloadLen;

    pinfo->ipProto = *(pinfo->espTrailer + 1); /* get Next Header */
#endif
    uint64_t cycles_start, cycles_end;
    MSG_DECMsgTypeDef *dec = (MSG_DECMsgTypeDef *)(skb->opaque + MSG_HEADER);
    NIC_RXDescTypeDef *rx_desc_seg;
    NIC_RXDescTypeDef *rx_desc_seg_last_second;

    uint32_t seg_len, i;
    /* get esp info */
    pinfo->espBufLen     = skb->dataLen - pinfo->ethLen - pinfo->ipLen; /* consider change */
    pinfo->espHdrLen     = 8;  /* not change */
    pinfo->espIVLen      = 8;  /* not change */
    pinfo->espTrailerLen = 2;  /* not change */
    /* The ICV consists solely of the AES-GCM Authentication Tag.
    Implementations MUST support a full-length 16-octet ICV, and MAY
    support 8 or 12 octet ICVs, and MUST NOT support other ICV lengths. */
    pinfo->espICVLen[3]     = 16; /* not change */

    pinfo->espBuf        = skb->data    + pinfo->ethLen + pinfo->ipLen;/* consider change */
    pinfo->espHdr        = pinfo->espBuf;  /* not change */
    pinfo->espIV         = pinfo->espHdr + pinfo->espHdrLen; /* not change */
    pinfo->espPayload[0] = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen;/* consider change */

    if(1 == pinfo->segs) {
        pinfo->espPayloadLen[0] = pinfo->espBufLen -
                                  pinfo->espHdrLen -
                                  pinfo->espIVLen -
                                  pinfo->espICVLen[3];  /* consider change */
        pinfo->espTrailer       = pinfo->espBuf +
                                  pinfo->espHdrLen +
                                  pinfo->espIVLen +
                                  (pinfo->espPayloadLen[0] - pinfo->espTrailerLen); /* consider change */
        pinfo->espICV[0]        = pinfo->espBuf +
                                  pinfo->espHdrLen +
                                  pinfo->espIVLen +
                                  pinfo->espPayloadLen[0]; /* consider change */
        pinfo->espICVLen[0]     = 16; /* not change */

    } else if(2 == pinfo->segs) {
        rx_desc_seg = (NIC_RXDescTypeDef *) dec->desc->desc11;
        seg_len = GET_FIELD(rx_desc_seg->desc0, 0, 0x3fff);  /* second seg length */
        if(seg_len < pinfo->espICVLen[3]) {                  /* pinfo->espICVLen[3] ---change to a macro*/
            /* pinfo->espBuflen - pinfo->espHdrlen - pinfo->espIVlen---change to a variable */
            pinfo->espPayloadLen[0] = pinfo->espBufLen -
                                      pinfo->espHdrLen -
                                      pinfo->espIVLen -
                                      (pinfo->espICVLen[3] - seg_len);  /* consider change */
            pinfo->espPayloadLen[1] = 0;
            pinfo->espTrailer       = pinfo->espBuf +
                                      pinfo->espHdrLen +
                                      pinfo->espIVLen +
                                      (pinfo->espPayloadLen[0] - pinfo->espTrailerLen); /* consider change */
            pinfo->espICV[0]        = pinfo->espBuf +
                                      pinfo->espHdrLen +
                                      pinfo->espIVLen +
                                      pinfo->espPayloadLen[0]; /* consider change */
            pinfo->espICVLen[0]     = pinfo->espICVLen[3] - seg_len;

            pinfo->espICV[1]        = rx_desc_seg->desc9;
            pinfo->espICVLen[1]     = seg_len;
            pinfo->espPayload[1]    = NULL;
        } else {
            pinfo->espPayloadLen[0] = pinfo->espBufLen -
                                      pinfo->espHdrLen -
                                      pinfo->espIVLen;  /* consider change */
            pinfo->espPayloadLen[1] = seg_len - pinfo->espICVLen[3];
            if(pinfo->espPayloadLen[1] >= pinfo->espTrailerLen) {  /* espTrailer location */
                pinfo->espTrailer       = rx_desc_seg->desc9 +
                                          (pinfo->espPayloadLen[1] - pinfo->espTrailerLen); /* consider change */
            } else {
                pinfo->espTrailer       = pinfo->espBuf +
                                          pinfo->espHdrLen +
                                          pinfo->espIVLen +
                                          (pinfo->espPayloadLen[0] - pinfo->espTrailerLen); /* consider change */
            }
            pinfo->espICV[0]        = rx_desc_seg->desc9 + pinfo->espPayloadLen[1];
            pinfo->espICVLen[0]     = pinfo->espICVLen[3];
            pinfo->espPayload[1]    = rx_desc_seg->desc9;
        }
    } else if (2 < pinfo->segs) {
            cycles_start = rdtsc_start();
            rx_desc_seg = (NIC_RXDescTypeDef *) dec->desc->desc11;  /* seg[1] */
            for (i = 0; i < (pinfo->segs - 2); i++) {
                rx_desc_seg = (NIC_RXDescTypeDef *)rx_desc_seg->desc11;  /* from seg[2] on */
                for (i = 0; pinfo->segs > 3, i < (pinfo->segs - 3); i++) { /* > 3 segments*/
                    pinfo->espPayload[i+1] = rx_desc_seg->desc9;
                    pinfo->espPayloadLen[i+1] = rx_desc_seg->desc0;
                }
                if(i == pinfo->segs - 1) {  /* last second  */
                    rx_desc_seg_last_second = rx_desc_seg;
                }
            }
            cycles_end = rdtsc_end();
            printf("time consumed %lu cycles\n", cycles_end - cycles_start);
            seg_len = GET_FIELD(rx_desc_seg->desc0, 0, 0x3fff);  /* second seg length */
            pinfo->espPayloadLen[0] = pinfo->espBufLen -
                                      pinfo->espHdrLen -
                                      pinfo->espIVLen;
            if(seg_len < pinfo->espICVLen[3]) {
                pinfo->espPayloadLen[pinfo->segs-2] = rx_desc_seg_last_second->desc0-
                                                      (pinfo->espICVLen[3] - seg_len);  /* consider change */
                pinfo->espPayloadLen[pinfo->segs-1] = 0;
                pinfo->espTrailer       = rx_desc_seg_last_second->desc9 +
                                          (pinfo->espPayloadLen[pinfo->segs-2] - pinfo->espTrailerLen); /* consider change */
                pinfo->espICV[0]        = rx_desc_seg_last_second->desc9  +
                                          pinfo->espPayloadLen[pinfo->segs-2]; /* consider change */
                pinfo->espICV[1]        = rx_desc_seg->desc9;
                pinfo->espPayload[2]    = NULL;
            } else {
                pinfo->espPayloadLen[pinfo->segs-2] = rx_desc_seg_last_second->desc0;
                pinfo->espPayloadLen[pinfo->segs-1] = seg_len - pinfo->espICVLen[3];
                if(pinfo->espPayloadLen[pinfo->segs-1] >= pinfo->espTrailerLen) {  /* espTrailer location */
                    pinfo->espTrailer       = rx_desc_seg->desc9 +
                                              (pinfo->espPayloadLen[pinfo->segs-1] - pinfo->espTrailerLen); /* consider change */
                } else {
                    pinfo->espTrailer       = rx_desc_seg_last_second->desc9  +
                                              (pinfo->espPayloadLen[pinfo->segs-2] - pinfo->espTrailerLen); /* consider change */
                }
                pinfo->espICV[0]        = rx_desc_seg->desc9 + pinfo->espPayloadLen[pinfo->segs-1];
                pinfo->espPayload[pinfo->segs-1]    = rx_desc_seg->desc9;
            }
        }

    pinfo->ipProto = *(pinfo->espTrailer + 1); /* get Next Header */
    return SECERR_OK;
}
#endif
__STATIC_FORCEINLINE
int Dissect_ESP(frameTableTypeDef *frameTable)
{
#if 0
    /* get esp info */
    pinfo->espBufLen     = skb->dataLen - pinfo->ethLen - pinfo->ipLen;
    pinfo->espHdrLen     = 8;
    pinfo->espIVLen      = 8;
    pinfo->espTrailerLen = 2;
    /* The ICV consists solely of the AES-GCM Authentication Tag.
    Implementations MUST support a full-length 16-octet ICV, and MAY
    support 8 or 12 octet ICVs, and MUST NOT support other ICV lengths. */
    pinfo->espICVLen     = 16;
    pinfo->espPayloadLen = pinfo->espBufLen -
                           pinfo->espHdrLen -
                           pinfo->espIVLen -
                           pinfo->espICVLen;
    pinfo->espBuf        = skb->data    + pinfo->ethLen + pinfo->ipLen;
    pinfo->espHdr        = pinfo->espBuf;
    pinfo->espIV         = pinfo->espHdr + pinfo->espHdrLen;
    pinfo->espPayload    = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen;
    pinfo->espTrailer    = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen +
                           (pinfo->espPayloadLen - pinfo->espTrailerLen);
    pinfo->espICV        = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen +
                           pinfo->espPayloadLen;

    pinfo->ipProto = *(pinfo->espTrailer + 1); /* get Next Header */
#endif
    uint64_t cycles_start, cycles_end;
    MSG_DECMsgTypeDef *dec = (MSG_DECMsgTypeDef *)(skb->opaque + MSG_HEADER);
    NIC_RXDescTypeDef *rx_desc_seg;
    NIC_RXDescTypeDef *rx_desc_seg_last_second;


    pinfo->ipProto = *(pinfo->espTrailer + 1); /* get Next Header */
    return SECERR_OK;
}
int Dissect_TCP(frameTableTypeDef *frameTable)
{
    /* Minimum TCP header length. */
#define TCPH_MIN_LEN            20

    uint8_t th_Off_X2;      /* combines th_off and th_x2 */
    uint32_t optLen;
    TCP_HDRTypeDef tcph;

    tcph.thSport = Get_ntohs(skb, 0);
    tcph.thDport = Get_ntohs(skb, 2);
    tcph.thSeq   = Get_ntohl(skb, 4);
    tcph.thACK   = Get_ntohl(skb, 8);
    th_Off_X2    = Get_UINT8(skb, 12);
    tcph.thHLen  = hi_nibble(th_Off_X2) * 4;
    tcph.thFlags = Get_ntohs(skb, 12) & TH_MASK;
    tcph.thWin   = Get_ntohs(skb, 14);
    tcph.thSum   = Get_ntohs(skb, 16);
    tcph.thURP   = Get_ntohs(skb, 18);

    optLen = tcph.thHLen - TCPH_MIN_LEN; /* length of options, in bytes */

    printf("    Transmission Control Protocol, Src Port: %u, Dst Port: %u, Seq: %u, Len: %u \n"
           "      Source Port: %u \n"
           "      Destination Port: %u \n"
           "      Sequence number: %u \n"
           "      Acknowledgment number: %u \n"
           "      Header Length: %u bytes (%u) \n"
           "      Flags: 0x%03x \n"
           "      Window size value: %u \n"
           "      Checksum: 0x%04x \n"
           "      Urgent pointer: %u \n"
           "      Options: (%u bytes) \n",
           tcph.thSport, tcph.thDport, tcph.thSeq, tcph.thHLen,
           tcph.thSport,
           tcph.thDport,
           tcph.thSeq,
           tcph.thACK,
           tcph.thHLen, tcph.thHLen >> 2,
           tcph.thFlags,
           tcph.thWin,
           tcph.thSum,
           tcph.thURP,
           optLen
          );

    return SECERR_OK;

#undef TCPH_MIN_LEN
}

int Dissect_UDP(frameTableTypeDef *frameTable)
{
    /* FIXME */
    return SECERR_OK;
}

int IP_Try_Dissect(frameTableTypeDef *frameTable)
{
    int ret = SECERR_INVAL;

    switch (frameTable->frame[0].ip.ipProto) {
    case IP_PROTO_ESP:
        ret = Dissect_ESP(frameTable);
        break;
    case IP_PROTO_TCP:
        ret = Dissect_TCP(frameTable);
        break;
    case IP_PROTO_UDP:
        ret = Dissect_UDP(frameTable);
        break;
    default:
        printf("Bogus IP proto \n");
        break;
    }
    return ret;
}

int dissect_IPv4(frameTableTypeDef *frameTable)
{
    /* Minimum IP header length. */
#define IPH_MIN_LEN             20

    uint32_t hLen, optLen;
    IPv4_HDRTypeDef iph;
    uint8_t srcStr[32], dstStr[32];

    iph.ipVer = Get_Bits8(skb, 0, 4);
    hLen = Get_Bits8(skb, 4, 4) * 4;  /* IP header length, in bytes */
    if ((hLen < IPH_MIN_LEN)) {
        printf("Bogus IP header length (%u, must be at least %u)",
               hLen, IPH_MIN_LEN);
        return SECERR_INVAL;
    }

    iph.ipTOS   = Get_UINT8(skb, IPH_TOS);
    iph.ipLen   = Get_ntohs(skb, IPH_LEN);
    iph.ipID    = Get_ntohs(skb, IPH_ID);
    iph.ipOff   = Get_ntohs(skb, IPH_OFF);
    iph.ipTTL   = Get_UINT8(skb, IPH_TTL);
    iph.ipProto = Get_UINT8(skb, IPH_P);
    iph.ipSum   = Get_ntohs(skb, IPH_SUM);
    setAddress(&iph.ipSrc, AT_IPv4, 4, skb->realData + IPH_SRC);
    setAddress(&iph.ipDst, AT_IPv4, 4, skb->realData + IPH_DST);
    pinfo->dst[0] = Get_ntohl(skb, IPH_DST);
    pinfo->addressType = AT_IPv4;
    printf("    Internet Protocol Version %u, Src: %s, Dst: %s\n",
           iph.ipVer,
           IPV4_TOStr(&iph.ipSrc, srcStr, sizeof(srcStr)),
           IPV4_TOStr(&iph.ipDst, dstStr, sizeof(dstStr)));
    printf("      %s\n",
           UINT_Bits_Format_Value(skb, 0, 4, " = Version: %u", iph.ipVer));
    printf("      %s\n",
           UINT_Bits_Format_Value(skb, 4, 4,
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
           iph.ipTOS,
           iph.ipLen,
           iph.ipID, iph.ipID,
           iph.ipOff,
           iph.ipTTL,
           Val_To_StrConst(iph.ipProto, IPProtoVals, "Unknown"), iph.ipProto,
           iph.ipSum,
           IPV4_TOStr(&iph.ipSrc, srcStr, sizeof(srcStr)),
           IPV4_TOStr(&iph.ipDst, dstStr, sizeof(dstStr)));

    pinfo->ipLen      = IPH_MIN_LEN;
    pinfo->ipProto    = iph.ipProto;
    skb->realData    += pinfo->ipLen;
    skb->realDataLen -= pinfo->ipLen;
    return IP_Try_Dissect(skb, pinfo);

#undef IPH_MIN_LEN
}

int dissect_IPv6(frameTableTypeDef *frameTable)
{
    /* FIXME */
    return SECERR_OK;
}

int Dissect_IP(frameTableTypeDef *frameTable)
{
    uint8_t version;
    int ret = SECERR_INVAL;

    version = *skb->realData >> 4;
    switch (version) {
    case 4:
        ret = dissect_IPv4(skb, pinfo);
        break;
    case 6:
        ret = dissect_IPv6(skb, pinfo);
        break;
    default:
        printf("Bogus IP version (%u)", version);
        break;
    }
    return ret;
}

int Dissect_Ethernet(frameTableTypeDef *frameTable)
{
    /* Minimum ETH header length. */
#define ETHH_MIN_LEN             14

    uint8_t srcStr[32];
    uint8_t dstStr[32];
    Eth_HDRTypeDef eHDR;

    setAddress(&eHDR.dst, AT_ETHER, 6, skb->realData);
    setAddress(&eHDR.src, AT_ETHER, 6, skb->realData + 6);
    eHDR.type = ntoh16(skb->realData + 12);

    printf("    Ethernet II, Src: %s, Dst: %s\n"
           "      Type: %s (0x%04x)\n",
           Ethernet_TOStr(&eHDR.src, srcStr, sizeof(srcStr)),
           Ethernet_TOStr(&eHDR.dst, dstStr, sizeof(dstStr)),
           Val_To_StrConst(eHDR.type, EtypeVals, "Unknown"), eHDR.type);

    pinfo->ethLen     = ETHH_MIN_LEN;
    skb->realData    += pinfo->ethLen;
    skb->realDataLen -= pinfo->ethLen;
    return Dissect_IP(skb, pinfo);

#undef ETHH_MIN_LEN
}

int Dissect_Frame(frameTableTypeDef *frameTable)
{
    printf("  Frame: %u bytes on wire \n", skb->dataLen);

    skb->realData    = skb->data;
    skb->realDataLen = skb->dataLen;
    return Dissect_Ethernet(skb, pinfo);
}
#else

__STATIC_FORCEINLINE
int Dissect_ESP(frameTableTypeDef *frameTable)
{
#if 0
    /* get esp info */
    pinfo->espBufLen     = skb->dataLen - pinfo->ethLen - pinfo->ipLen;
    pinfo->espHdrLen     = 8;
    pinfo->espIVLen      = 8;
    pinfo->espTrailerLen = 2;
    /* The ICV consists solely of the AES-GCM Authentication Tag.
    Implementations MUST support a full-length 16-octet ICV, and MAY
    support 8 or 12 octet ICVs, and MUST NOT support other ICV lengths. */
    pinfo->espICVLen     = 16;
    pinfo->espPayloadLen = pinfo->espBufLen -
                           pinfo->espHdrLen -
                           pinfo->espIVLen -
                           pinfo->espICVLen;
    pinfo->espBuf        = skb->data    + pinfo->ethLen + pinfo->ipLen;
    pinfo->espHdr        = pinfo->espBuf;
    pinfo->espIV         = pinfo->espHdr + pinfo->espHdrLen;
    pinfo->espPayload    = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen;
    pinfo->espTrailer    = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen +
                           (pinfo->espPayloadLen - pinfo->espTrailerLen);
    pinfo->espICV        = pinfo->espBuf +
                           pinfo->espHdrLen +
                           pinfo->espIVLen +
                           pinfo->espPayloadLen;

    pinfo->ipProto = *(pinfo->espTrailer + 1); /* get Next Header */
#endif
    uint64_t cycles_start, cycles_end;
    uint32_t segs_total_len;
    MSG_DECMsgTypeDef *dec = (MSG_DECMsgTypeDef *)(skb->opaque + MSG_HEADER);
    uint32_t seg_len, i;
    uint8_t *espPayload;
    uint32_t espPayloadLen;
    uint32_t state = s_Hdr;
    uint32_t offset_len;
    segs_total_len = GET_FIELD(dec->desc->desc6, 16, 0xffff);

    for (;;) {
        switch(state)
        {
            case s_Hdr:
                /* frameTable->frame[0].esp.espBufLen = frameTable->frame[0].origDataLen - frameTable->frame[0].eth.ethLen - frameTable->frame[0].ip.ipLen; */
                frameTable->frame[0].esp.espHdrLen = 8;
                frameTable->frame[0].esp.espIVLen = 8;
                frameTable->frame[0].esp.espHdr = frameTable->frame[0].origData + frameTable->frame[0].eth.ethLen + frameTable->frame[0].ip.ipLen;
                espPayloadLen = segs_total_len -
                                frameTable->frame[0].eth.ethLen -
                                frameTable->frame[0].ip.ipLen -
                                frameTable->frame[0].esp.espHdrLen -
                                frameTable->frame[0].esp.espIVLen -
                                frameTable->frame[0].esp.espICVLen;
                offset_len = frameTable->frame[0].eth.ethLen +
                             frameTable->frame[0].ip.ipLen +
                             frameTable->frame[0].esp.espHdrLen +
                             frameTable->frame[0].esp.espIVLen;
                /* segs_total_len -= (frameTable->frame[0].eth.ethLen + */
                /*                    frameTable->frame[0].ip.ipLen + */
                /*                    frameTable->frame[0].esp.espHdrLen + */
                /*                    frameTable->frame[0].esp.espIVLen); */
                state = s_EspPayload;
                continue;
            case s_EspPayload:
                for (i = 0; i < frameTable->origNents; ++i) {
                    if(segs_total_len <= frameTable->frame[i].origDataLen) {
                        frameTable->frame[i].esp.espPayload = frameTable->frame[i].origData + offset_len;
                        frameTable->frame[i].esp.espPayloadLen = espPayloadLen;
                        state = s_EspTrailer;
                        continue;
                    }
                    else
                    {
                        frameTable->frame[i].esp.espPayload = frameTable->frame[i].origData + offset_len;
                        frameTable->frame[i].esp.espPayloadLen = espPayloadLen;
                        segs_total_len -= frameTable->frame[i].origDataLen;
                    }
                }
                continue;
            case s_EspTrailer:

                continue;
            case s_EspICV:

                continue;
        }
        /* if(frameTable->frame[i].origDataLen < segs_total_len) { */
        /*     continue; */
        /* } */
    }
    /* pinfo->ipProto = *(pinfo->espTrailer + 1); /\* get Next Header *\/ */
    return SECERR_OK;
}

__STATIC_FORCEINLINE
int IP_Try_Dissect(frameTableTypeDef *frameTable)
{
    int ret = SECERR_INVAL;

    switch (frameTable->frame[0].ip.ipProto) {
    case IP_PROTO_ESP:
        ret = Dissect_ESP(frameTable);
        break;
    default:
        printf("Bogus IP proto \n");
        break;
    }

    return ret;
}

int Dissect_Frame(frameTableTypeDef *frameTable)
{
    int ret = SECERR_INVAL;

    frameTable->frame[0].ethLen = 14; /* Minimum ETH header length. */

    /* IP version(v4 or v6) */
    switch (*(frameTable->frame[0].origData  + frameTable->frame[0].eth.ethLen) >> 4) {
    case 4:
        frameTable->frame[0].eth.addressType = AT_IPv4;
        frameTable->frame[0].ip.ipLen       = 20; /* Minimum IP header length. */
        frameTable->frame[0].eth.dst[0]      = ntoh32(frameTable->frame[0].origData + frameTable->frame[0].eth.ethLen + IPH_DST);
        frameTable->frame[0].ip.ipProto     = *(frameTable->frame[0].origData + frameTable->frame[0].eth.ethLen + IPH_P);
        ret = IP_Try_Dissect(frameTable);
        break;
    case 6:
        /* FIXME */
        frameTable->frame[0].eth.addressType = AT_IPv6;
        break;
    default:
        printf("Bogus IP version \n");
        break;
    }

    return ret;
}
#endif
