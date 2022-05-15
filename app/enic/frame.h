
#ifndef _FRAME_H
#define _FRAME_H

#define DEBUG

#include "address.h"

enum
{
    OUTBOUND = 0,               /* TX, Encryption */
    INBOUND  = 1                /* RX, Decryption */
};

/* IP protocol numbers. */
#define IP_PROTO_TCP    6       /* TCP - RFC792 */
#define IP_PROTO_ESP    50      /* Encap Security Payload for IPv6 - RFC2406 */

/* Offsets of fields within an IP header. */
#define IPH_V_HL        0
#define IPH_TOS         1
#define IPH_LEN         2
#define IPH_ID          4
#define IPH_TTL         6
#define IPH_OFF         8
#define IPH_P           9
#define IPH_SUM         10
#define IPH_SRC         12
#define IPH_DST         16

typedef struct
{
    uint32_t direction;

    uint8_t *espBuf;
    uint32_t espBufLen;

    uint8_t *espPayload;
    uint32_t espPayloadLen;

    uint8_t *espICV;
    uint32_t espICVLen;

    uint32_t espHdrLen;
    uint32_t espIVLen;
    uint32_t espTrailerLen;
} IPSecTypeDef;

typedef struct
{
    uint32_t addressType;
    uint32_t len;
    uint32_t ipDst[4];
} IPTypeDef;

typedef struct
{
    uint32_t len;
} EthTypeDef;

typedef struct
{
    uint32_t 	spi;			/**< Security Parameters Index      */
    uint32_t	sequence_number;/**< Sequence number                */
} espHdrPacket;


typedef struct {
    uint8_t *data;
    uint32_t dataLen;
#ifdef DEBUG
    uint8_t *realData;
    uint32_t realDataLen;
#endif
} skBufTypeDef;

typedef struct
{
    skBufTypeDef skBuf;
    EthTypeDef   eth;
    IPTypeDef    ip;
    IPSecTypeDef ipsec;
    intptr_t     opaque;
} FrameTypeDef;

#endif /* _FRAME_H */
