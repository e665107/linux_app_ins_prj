
#ifndef _PACKET_FRAME_H
#define _PACKET_FRAME_H

#include "address.h"

enum {
    OUTBOUND = 0,               /* TX, Encryption */
    INBOUND  = 1                /* RX, Decryption */
};

typedef struct {
    uint8_t *hdr;
    uint32_t hdrLen;
} EthTypeDef;

typedef struct {
    uint8_t *hdr;
    uint32_t hdrLen;
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
    IPTypeDef ip;
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
    uint8_t direction;
    uint32_t containedLen;
    unsigned int nents;         /* number of mapped entries */
    frameTypeDef frame[6];      /* the list */
} frameTableTypeDef;

__STATIC_FORCEINLINE
uint8_t Frame_IP_Ver(frameTableTypeDef *frameTable)
{
    return (*(frameTable->frame[0].ip.hdr) >> 4);
}

int Dissect_Frame(frameTableTypeDef *frameTable);

#endif /* _PACKET_FRAME_H */

