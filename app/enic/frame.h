-
#ifndef _FRAME_H
#define _FRAME_H

#include "address.h"
enum
{
    OUTBOUND = 0,                   /* TX, Encryption */
    INBOUND  = 1                    /* RX, Decryption */
};

/* IP protocol numbers. */
#define IP_PROTO_TCP        6       /* TCP - RFC792 */
#define IP_PROTO_UDP        17      /* user datagram protocol - RFC768 */
#define IP_PROTO_ESP        50      /* Encap Security Payload for IPv6 - RFC2406 */
#define IP_PROTO_UDPLITE    136     /* Lightweight user datagram protocol - RFC3828 */

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

typedef struct
{
    uint32_t segs;
    uint32_t direction;
    uint32_t addressType;
    uint32_t ethLen;
    uint32_t ipProto;
    uint32_t ipLen;
    uint32_t dst[4];
    uint32_t src[4];
    uint16_t addressType;
    uint32_t ethLen;
} EthTypeDef;

typedef struct {
    uint8_t  ipVer;     /* 4 */
    uint8_t  ipTos;     /* type of service */
    uint32_t ipLen;     /* total length */
    uint16_t ipID;      /* identification */
    uint16_t ipOff;     /* fragment offset */
    uint8_t  ipTTL;     /* time-to-live */
    uint8_t  ipProto;   /* protocol */
    uint16_t ipSum;     /* checksum */
    uint32_t ipSrc[4];  /* source address */
    uint32_t ipDst[4];  /* destination address */
} IPTypeDef;

typedef struct {
    uint8_t *espBuf;
    uint32_t espBufLen;
    uint8_t *espHdr;
    uint32_t espHdrLen;
    uint8_t *espIV;
    uint32_t espIVLen;
    uint8_t *espPayload;
    uint32_t espPayloadLen[8];
    uint8_t *espTrailer;
    uint32_t espTrailerLen;
    uint8_t *espICV;
    uint32_t espICVLen;
} ESPTypeDef;

typedef struct {
    EthTypeDef eth;
    IPTypeDef  ip;
    ESPTypeDef esp;
    uint8_t *origData;
    uint32_t origDataLen;
    /* NIC_RXDescTypeDef *rx_desc_seg; */
    /* uint32_t leftDataLen; */
} frameTypeDef;

typedef struct {
    frameTypeDef frame[6];      /* the list */
    unsigned int direction;
    unsigned int nents;         /* number of mapped entries */
    unsigned int origNents;     /* original size of list */
} frameTableTypeDef;

typedef struct
{
    uint32_t 	spi;			/**< Security Parameters Index */
    uint32_t	sequence_number;        /**< Sequence number */
} espHdrPacket;


#endif /* _FRAME_H */
