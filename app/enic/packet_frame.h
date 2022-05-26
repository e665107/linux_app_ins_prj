-
#ifndef _PACKET_FRAME_H
#define _PACKET_FRAME_H

#include "frame.h"

enum state
{
    s_Hdr = 1,
    s_EspPayload,
    s_EspTrailer,
    s_EspICV
};
uint64_t rdtsc_start(void);
uint64_t rdtsc_end(void);

int Dissect_Frame(skbufTypeDef *skb, Packet_InfoTypeDef *pinfo);

#endif /* _PACKET_FRAME_H */
