-
#ifndef _PACKET_FRAME_H
#define _PACKET_FRAME_H

#include "frame.h"

typedef enum state
{
    s_EthHdr = 1,
    s_IpHdr,
    s_EspHdr,
    s_EspPayload,
    s_EspTrailer,
    s_EspICV
} Esp_State;
uint64_t rdtsc_start(void);
uint64_t rdtsc_end(void);

int Dissect_Frame(skbufTypeDef *skb, Packet_InfoTypeDef *pinfo);

#endif /* _PACKET_FRAME_H */
