
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
    uint32_t espPayload_start_Flag;
    uint32_t espPayload_end_Flag;
    uint32_t espTrailer_Flag;
    uint32_t espICV_Flag;
    uint8_t espPayload_Start_seg;
    uint8_t espPayload_End_seg;
    uint8_t espTrailer_Start_seg;
    uint8_t espICV_Start_seg ;
} fieldlocationTypeDef;

typedef struct {
    uint8_t direction;
    uint32_t containedLen;
    unsigned int nents;         /* number of mapped entries */
    frameTypeDef frame[6];      /* the list */
    fieldlocationTypeDef locationMark;
} frameTableTypeDef;

__STATIC_FORCEINLINE
uint8_t Frame_IP_Ver(frameTableTypeDef *frameTable)
{
    return (*(frameTable->frame[0].ip.hdr) >> 4);
}
#if 1
__STATIC_FORCEINLINE
void Frame_ESP_Payload_to_BufferList(frameTableTypeDef *frameTable, BufferListTypedef *BufferList)
{
#if 1
    uint32_t i;
    uint32_t padding_len;

    for (i = frameTable->locationMark.espPayload_Start_seg; i <=
             frameTable->locationMark.espPayload_End_seg; ++i) {
               BufferList->buffers[i].data = frameTable->frame[i].esp.payload;
               BufferList->buffers[i].dataLen = frameTable->frame[i].esp.payloadLen;
               BufferList->numBuffers++;
    }

    padding_len = *frameTable->frame[frameTable->locationMark.espTrailer_Start_seg].esp.trailer;

    for (i; i > 0; i--) {
        if(BufferList->buffers[i].dataLen > padding_len) {
            BufferList->buffers[i].dataLen -= padding_len;
            break;
        }
        else {
            padding_len -= BufferList->buffers[i].dataLen;
            BufferList->buffers[i].data = NULL;
        }
    }
#endif
}
#endif
int Dissect_Frame(frameTableTypeDef *frameTable);

#endif /* _PACKET_FRAME_H */
