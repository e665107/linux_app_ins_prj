
#ifndef _FRAME_H
#define _FRAME_H

enum {
    OUTBOUND = 0,                   /* TX, Encryption */
    INBOUND  = 1                    /* RX, Decryption */
};

typedef struct {
    uint32_t dst[4];
    uint32_t src[4];
    uint16_t type;
} EthTypeDef;

typedef struct {
    uint8_t  ver;               /* 4 */
    uint8_t  tos;               /* type of service */
    uint32_t len;               /* total length */
    uint16_t id;                /* identification */
    uint16_t off;               /* fragment offset */
    uint8_t  ttl;               /* time-to-live */
    uint8_t  proto;             /* protocol */
    uint16_t sum;               /* checksum */
    uint32_t src[4];            /* source address */
    uint32_t dst[4];            /* destination address */
} IPTypeDef;

typedef struct {
    uint8_t *hdr;
    uint32_t hdrLen;
    uint8_t *iv;
    uint32_t ivLen;
    uint8_t *payload;
    uint32_t payloadLen;
    uint8_t *trailer;
    uint32_t trailerLen;
    uint8_t *icv;
    uint32_t icvLen;
} ESPTypeDef;

typedef struct {
    EthTypeDef eth;
    IPTypeDef  ip;
    ESPTypeDef esp;
    uint8_t *data;
    uint32_t dataLen;
    /* Amount of data that was reported as being in
     * the packet or other data that this represents.
     * As indicated above, it may be greater than the
     * amount of data that's available.
     */
    uint32_t reportedLen;
} frameTypeDef;

typedef struct {
    unsigned int nents;         /* number of mapped entries */
    frameTypeDef frame[6];      /* the list */
} frameTableTypeDef;

#endif /* _FRAME_H */

