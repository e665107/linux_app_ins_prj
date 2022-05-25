
#ifndef _PACKET_FRAME_H
#define _PACKET_FRAME_H

#include "frame.h"
uint64_t rdtsc_start(void);
uint64_t rdtsc_end(void);

int Dissect_Frame(skbufTypeDef *skb, Packet_InfoTypeDef *pinfo);

#endif /* _PACKET_FRAME_H */

