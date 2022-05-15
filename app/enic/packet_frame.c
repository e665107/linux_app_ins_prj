
#include <stdio.h>
#include <string.h>

#include "inet.h"
#include "frame.h"


#define SECERR_OK           0x0
#define SECERR_INVAL        0x1  /* Invalid IPsec Protocol */
#define SECERR_INVAL_LEN    0x2
#define SECERR_INVAL_AUTH   0x3

#ifdef DEBUG
int IP_Try_Dissect(FrameTypeDef *frame, uint8_t ipProto);

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

typedef struct
{
    uint32_t value;
    const uint8_t *strptr;
} Value_StringTypeDef;

/* the tcp header structure, passed to tap listeners */
typedef struct
{
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

typedef struct
{
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

typedef struct
{
    AddressTypeDef dst;
    AddressTypeDef src;
    uint16_t type;
} Eth_HDRTypeDef;

static
const uint8_t bitMask8[] =
{
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

static const char fastStrings[][4] =
{
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
const Value_StringTypeDef EtypeVals[] =
{
    {ETHERTYPE_IP,      "IPv4"},
    {ETHERTYPE_IPv6,    "IPv6"},
    {0,                 NULL  }
};

static
const Value_StringTypeDef IPProtoVals[] =
{
    {IP_PROTO_TCP,      "TCP"                   },  /* [RFC793] */
    {IP_PROTO_ESP,      "Encap Security Payload"},  /* [RFC4303] */
    {0,                 NULL                    },
};

const uint8_t *fastEnsureContiguous(skBufTypeDef *skb,
                                    const int offset,
                                    const uint32_t length)
{
    uint32_t endOffset;
    uint32_t uOffset;

    uOffset = offset;
    endOffset = uOffset + length;

    if (endOffset <= skb->realDataLen)
    {
        return skb->realData + uOffset;
    }

    /* not reached */
    return NULL;
}

uint8_t Get_UINT8(skBufTypeDef *skb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(skb, offset, 1);
    return *ptr;
}

uint16_t Get_ntohs(skBufTypeDef *skb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(skb, offset, 2);
    return ntoh16(ptr);
}

uint32_t Get_ntohl(skBufTypeDef *skb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(skb, offset, 4);
    return ntoh32(ptr);
}

uint64_t Get_ntoh64(skBufTypeDef *skb, const int offset)
{
    const uint8_t *ptr;

    ptr = fastEnsureContiguous(skb, offset, 8);
    return ntoh64(ptr);
}

uint64_t Get_Bits64(skBufTypeDef *skb,
                    uint32_t bitOffset,
                    const int32_t Total_No_Of_Bits)
{
    uint64_t value;
    uint32_t octetOffset = bitOffset >> 3;
    uint8_t  Required_Bits_In_First_Octet = 8 - (bitOffset % 8);

    if (Required_Bits_In_First_Octet > Total_No_Of_Bits)
    {
        /* the required bits don't extend to the end of the first octet */
        uint8_t rightShift = Required_Bits_In_First_Octet - Total_No_Of_Bits;
        value = (Get_UINT8(skb, octetOffset) >> rightShift) & bitMask8[Total_No_Of_Bits % 8];
    }
    else
    {
        uint8_t remainingBitLength = Total_No_Of_Bits;

        /* get the bits up to the first octet boundary */
        value = 0;
        Required_Bits_In_First_Octet %= 8;
        if (Required_Bits_In_First_Octet != 0)
        {
            value = Get_UINT8(skb, octetOffset) & bitMask8[Required_Bits_In_First_Octet];
            remainingBitLength -= Required_Bits_In_First_Octet;
            octetOffset++;
        }
        /* take the biggest words, shorts or octets that we can */
        while (remainingBitLength > 7)
        {
            switch (remainingBitLength >> 4)
            {
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
        if (remainingBitLength)
        {
            value <<= remainingBitLength;
            value += (Get_UINT8(skb, octetOffset) >> (8 - remainingBitLength));
        }
    }

    return value;
}

/* Get 1 - 8 bits */
uint8_t Get_Bits8(skBufTypeDef *skb,
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

    if (vs)
    {
        while (vs[i].strptr)
        {
            if (vs[i].value == val)
            {
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
    static const uint8_t hex_digits[16] =
    {
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
    for (i = 1; i < len; i++)
    {
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
    do
    {
        *b++ = *p;
        p++;
    }
    while (*p);
    *b++ = '.';

    p = fastStrings[*ad++];
    do
    {
        *b++ = *p;
        p++;
    }
    while (*p);
    *b++ = '.';

    p = fastStrings[*ad++];
    do
    {
        *b++ = *p;
        p++;
    }
    while (*p);
    *b++ = '.';

    p = fastStrings[*ad];
    do
    {
        *b++ = *p;
        p++;
    }
    while (*p);
    *b = 0;
}

const uint8_t *IPV4_TOStr(const AddressTypeDef *addr,
                          uint8_t *buf, int bufLen)
{
    IP_To_STR_Buf((const uint8_t *)addr->data, buf, bufLen);
    return buf;
    //return (int)(strlen(buf)+1);
}

int Dissect_ESP(FrameTypeDef *frame)
{
    IPSecTypeDef *ipsec  = &frame->ipsec;
    ipsec->espBuf        = frame->skBuf.realData;
    ipsec->espBufLen     = frame->skBuf.realDataLen;
    ipsec->espHdrLen     = 8;
    ipsec->espIVLen      = 8;
    ipsec->espTrailerLen = 2;
    /* The ICV consists solely of the AES-GCM Authentication Tag.
     Implementations MUST support a full-length 16-octet ICV, and MAY
     support 8 or 12 octet ICVs, and MUST NOT support other ICV lengths. */
    ipsec->espICVLen     = 16;

    ipsec->espPayload    = ipsec->espBuf +
                           ipsec->espHdrLen +
                           ipsec->espIVLen;
    ipsec->espPayloadLen = ipsec->espBufLen -
                           ipsec->espHdrLen -
                           ipsec->espIVLen -
                           ipsec->espTrailerLen -
                           ipsec->espICVLen;
    ipsec->espICV        = ipsec->espBuf +
                           ipsec->espHdrLen +
                           ipsec->espIVLen +
                           ipsec->espPayloadLen +
                           ipsec->espTrailerLen;

    {
        uint32_t spi = 0;
        uint32_t sequenceNumber;

        spi = Get_ntohl(&frame->skBuf, 0);
        sequenceNumber = Get_ntohl(&frame->skBuf, 4);

        printf("    Encapsulating Security Payload \n"
               "      ESP SPI: 0x%08x (%u) \n"
               "      ESP Sequence: %u \n",
               spi, spi,
               sequenceNumber);

        switch (ipsec->direction)
        {
            case INBOUND:
                {
                }
                break;
            case OUTBOUND:
                {
                    uint64_t iv;
                    uint8_t esp_Pad_Len;
                    uint8_t encapsulated_Protocol;

                    iv = Get_ntoh64(&frame->skBuf, ipsec->espHdrLen);
                    esp_Pad_Len =
                        Get_UINT8(
                            &frame->skBuf,
                            ipsec->espBufLen - (ipsec->espTrailerLen +
                                                ipsec->espICVLen));
                    encapsulated_Protocol =
                        Get_UINT8(
                            &frame->skBuf,
                            ipsec->espBufLen - (ipsec->espTrailerLen +
                                                ipsec->espICVLen + 1));
                    printf("      ESP IV: %016lx \n"
                           "      ESP Pad Length: %u \n"
                           "      Next header: %s (0x%02x) \n"
                           "      Authentication Data \n",
                           iv,
                           esp_Pad_Len,
                           Val_To_StrConst(encapsulated_Protocol,
                                           IPProtoVals,
                                           "Unknown"),
                           encapsulated_Protocol);

                    frame->skBuf.realData    = frame->ipsec.espPayload;
                    frame->skBuf.realDataLen = frame->ipsec.espPayloadLen - esp_Pad_Len;
                    IP_Try_Dissect(frame, encapsulated_Protocol);
                }
                break;
        }
    }

    return SECERR_OK;
}

int Dissect_TCP(FrameTypeDef *frame)
{
    /* Minimum TCP header length. */
#define TCPH_MIN_LEN            20

    uint8_t th_Off_X2;      /* combines th_off and th_x2 */
    uint32_t optLen;
    TCP_HDRTypeDef tcph;

    tcph.thSport = Get_ntohs(&frame->skBuf, 0);
    tcph.thDport = Get_ntohs(&frame->skBuf, 2);
    tcph.thSeq   = Get_ntohl(&frame->skBuf, 4);
    tcph.thACK   = Get_ntohl(&frame->skBuf, 8);
    th_Off_X2    = Get_UINT8(&frame->skBuf, 12);
    tcph.thHLen  = hi_nibble(th_Off_X2) * 4;
    tcph.thFlags = Get_ntohs(&frame->skBuf, 12) & TH_MASK;
    tcph.thWin   = Get_ntohs(&frame->skBuf, 14);
    tcph.thSum   = Get_ntohs(&frame->skBuf, 16);
    tcph.thURP   = Get_ntohs(&frame->skBuf, 18);

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

int IP_Try_Dissect(FrameTypeDef *frame, uint8_t ipProto)
{
    int ret = SECERR_INVAL;

    switch (ipProto)
    {
        case IP_PROTO_ESP:
            ret = Dissect_ESP(frame);
            break;
        case IP_PROTO_TCP:
            ret = Dissect_TCP(frame);
            break;
        default:
            break;
    }
    return ret;
}

int dissect_IPv4(FrameTypeDef *frame)
{
    /* Minimum IP header length. */
#define IPH_MIN_LEN             20

    uint32_t hLen, optLen;
    IPv4_HDRTypeDef iph;
    uint8_t srcStr[32], dstStr[32];

    iph.ipVer = Get_Bits8(&frame->skBuf, 0, 4);
    hLen = Get_Bits8(&frame->skBuf, 4, 4) * 4;  /* IP header length, in bytes */
    if ((hLen < IPH_MIN_LEN))
    {
        printf("Bogus IP header length (%u, must be at least %u)",
               hLen, IPH_MIN_LEN);
        return SECERR_INVAL;
    }

    iph.ipTOS   = Get_UINT8(&frame->skBuf, 1);
    iph.ipLen   = Get_ntohs(&frame->skBuf, 2);
    iph.ipID    = Get_ntohs(&frame->skBuf, 4);
    iph.ipOff   = Get_ntohs(&frame->skBuf, 6);
    iph.ipTTL   = Get_ntohs(&frame->skBuf, 8);
    iph.ipProto = Get_UINT8(&frame->skBuf, 9);
    iph.ipSum   = Get_ntohs(&frame->skBuf, 10);
    setAddress(&iph.ipSrc, AT_IPv4, 4, frame->skBuf.realData + IPH_SRC);
    setAddress(&iph.ipDst, AT_IPv4, 4, frame->skBuf.realData + IPH_DST);
    frame->ip.ipDst[0] = Get_ntohl(&frame->skBuf, IPH_DST);

    printf("    Internet Protocol Version %u, Src: %s, Dst: %s\n"
           "      Differentiated Services Field: 0x%02x\n"
           "      Total Length: %u\n"
           "      Identification: 0x%04x (%u)\n"
           "      Flags: 0x%04x\n"
           "      Time to live: %u\n"
           "      Protocol: %s (%u)\n"
           "      Header checksum: 0x%04x\n"
           "      Source: %s\n"
           "      Destination: %s\n",
           iph.ipVer,
           IPV4_TOStr(&iph.ipSrc, srcStr, sizeof(srcStr)),
           IPV4_TOStr(&iph.ipDst, dstStr, sizeof(dstStr)),
           iph.ipTOS,
           iph.ipLen,
           iph.ipID, iph.ipID,
           iph.ipOff,
           iph.ipTTL,
           Val_To_StrConst(iph.ipProto, IPProtoVals, "Unknown"), iph.ipProto,
           iph.ipSum,
           IPV4_TOStr(&iph.ipSrc, srcStr, sizeof(srcStr)),
           IPV4_TOStr(&iph.ipDst, dstStr, sizeof(dstStr)));

    frame->ip.len = IPH_MIN_LEN;
    frame->skBuf.realData    += frame->ip.len;
    frame->skBuf.realDataLen -= frame->ip.len;
    return IP_Try_Dissect(frame, iph.ipProto);

#undef IPH_MIN_LEN
}

int dissect_IPv6(FrameTypeDef *frame)
{
    /* FIXME */
    return SECERR_OK;
}

int Dissect_IP(FrameTypeDef *frame)
{
    uint8_t version;
    int ret = SECERR_INVAL;

    version = *frame->skBuf.realData >> 4;
    switch (version)
    {
        case 4:
            ret = dissect_IPv4(frame);
            break;
        case 6:
            ret = dissect_IPv6(frame);
            break;
        default:
            printf("Bogus IP version (%u)", version);
            break;
    }
    return ret;
}

int Dissect_Ethernet(FrameTypeDef *frame)
{

    uint8_t srcStr[32];
    uint8_t dstStr[32];
    Eth_HDRTypeDef eHDR;

    setAddress(&eHDR.dst, AT_ETHER, 6, frame->skBuf.realData);
    setAddress(&eHDR.src, AT_ETHER, 6, frame->skBuf.realData + 6);
    eHDR.type = ntoh16(frame->skBuf.realData + 12);

    printf("    Ethernet II, Src: %s, Dst: %s\n"
           "      Type: %s (0x%04x)\n",
           Ethernet_TOStr(&eHDR.src, srcStr, sizeof(srcStr)),
           Ethernet_TOStr(&eHDR.dst, dstStr, sizeof(dstStr)),
           Val_To_StrConst(eHDR.type, EtypeVals, "Unknown"), eHDR.type);

    frame->eth.len = 14;
    frame->skBuf.realData    += frame->eth.len;
    frame->skBuf.realDataLen -= frame->eth.len;
    return Dissect_IP(frame);
}

int Dissect_Frame(FrameTypeDef *frame)
{
    printf("  Frame: %u bytes on wire \n", frame->skBuf.dataLen);

    frame->skBuf.realData = frame->skBuf.data;
    frame->skBuf.realDataLen = frame->skBuf.dataLen;
    return Dissect_Ethernet(frame);
}
#else
__STATIC_FORCEINLINE
int Dissect_ESP(FrameTypeDef *frame)
{
    IPSecTypeDef *ipsec  = &frame->ipsec;

    ipsec->espBuf        = frame->skBuf.data    + frame->eth.len + frame->ip.len;
    ipsec->espBufLen     = frame->skBuf.dataLen - frame->eth.len - frame->ip.len;
    ipsec->espHdrLen     = 8;
    ipsec->espIVLen      = 8;
    ipsec->espTrailerLen = 2;
    /* The ICV consists solely of the AES-GCM Authentication Tag.
     Implementations MUST support a full-length 16-octet ICV, and MAY
     support 8 or 12 octet ICVs, and MUST NOT support other ICV lengths. */
    ipsec->espICVLen     = 16;

    ipsec->espPayload    = ipsec->espBuf +
                           ipsec->espHdrLen +
                           ipsec->espIVLen;
    ipsec->espPayloadLen = ipsec->espBufLen -
                           ipsec->espHdrLen -
                           ipsec->espIVLen -
                           ipsec->espTrailerLen -
                           ipsec->espICVLen;
    ipsec->espICV        = ipsec->espBuf +
                           ipsec->espHdrLen +
                           ipsec->espIVLen +
                           ipsec->espPayloadLen +
                           ipsec->espTrailerLen;
    return SECERR_OK;
}

__STATIC_FORCEINLINE
int IP_Try_Dissect(FrameTypeDef *frame, uint8_t ipProto)
{
    int ret = SECERR_INVAL;

    switch (ipProto)
    {
        case IP_PROTO_ESP:
            ret = Dissect_ESP(frame);
            break;
        default:
            printf("Bogus IP proto \n");
            break;
    }

    return ret;
}

int Dissect_Frame(FrameTypeDef *frame)
{
    int ret = SECERR_INVAL;

    frame->eth.len = 14;

    /* IP version(v4 or v6) */
    switch (*(frame->skBuf.data + frame->eth.len) >> 4)
    {
        case 4:
            frame->ip.addressType = AT_IPv4;
            frame->ip.len = 20; /* Minimum IP header length. */
            frame->ip.ipDst[0] = ntoh32(frame->skBuf.data + frame->eth.len + IPH_DST);
            ret = IP_Try_Dissect(frame, *(frame->skBuf.data + frame->eth.len + IPH_P));
            break;
        case 6:
            /* FIXME */
            frame->ip.addressType = AT_IPv6;
            break;
        default:
            printf("Bogus IP version \n");
            break;
    }

    return ret;
}
#endif
