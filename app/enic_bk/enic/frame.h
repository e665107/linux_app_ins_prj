
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

} Packet_InfoTypeDef;

struct scatterlist {
    uint8_t *espBuf;
    uint32_t espBufLen;
    uint8_t *espHdr;
    uint32_t espHdrLen;
    uint8_t *espIV;
    uint32_t espIVLen;
    uint8_t *espPayload;
    uint32_t espPayloadLen;
    uint8_t *espTrailer;
    uint32_t espTrailerLen;
    uint8_t *espICV;
    uint32_t espICVLen;
};

struct sg_table {
	struct scatterlist *sgl;	/* the list */
	unsigned int nents;		/* number of mapped entries */
	unsigned int orig_nents;	/* original size of list */
};



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
    intptr_t opaque;
} skbufTypeDef;

#endif /* _FRAME_H */
