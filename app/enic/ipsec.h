
#ifndef _IPSEC_H
#define _IPSEC_H

/*

RFC4303 - IP Encapsulating Security Payload (ESP)

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |               Security Parameters Index (SPI)                 |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                      Sequence Number                          |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+---
  |                    IV (optional)                              | ^ p
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ | a
  |                    Rest of Payload Data (variable)            | | y
  ˜                                                               ˜ | l
  |                                                               | | o
  +               +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ | a
  |               |         TFC Padding * (optional, variable)    | v d
  +-+-+-+-+-+-+-+-+         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+---
  |                         |        Padding (0-255 bytes)        |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |                               | Pad Length    | Next Header   |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  |         Integrity Check Value-ICV (variable)                  |
  ˜                                                               ˜
  |                                                               |
  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                 Figure Substructure of Payload Data

 */

void IPSec_Loop(intptr_t msg);
uint32_t SA_RX_LOOKUP(intptr_t msg);
void Rx_SA_Find(uint32_t *daddr, uint32_t spi, int ip4);

#endif /* _IPSEC_H */
