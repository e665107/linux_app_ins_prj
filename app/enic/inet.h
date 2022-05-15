
#ifndef __INET_H
#define __INET_H

#include <nmsis_core.h>

/* Swap bytes in 16-bit value.  */
#define bswap_constant_16(x) \
    ((uint16_t) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))

/* Swap bytes in 32-bit value.  */
#define bswap_constant_32(x) \
    ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8) \
     | (((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24))

__STATIC_FORCEINLINE
uint16_t htons(uint16_t x)
{
    return bswap_constant_16(x);
}

__STATIC_FORCEINLINE
uint32_t htonl(uint32_t x)
{
    return bswap_constant_32(x);
}

#if 0
__STATIC_FORCEINLINE
uint16_t ntohs(const void *p)
{
    return (uint16_t) * ((const uint8_t *)(p) + 0) << 8 |
           (uint16_t) * ((const uint8_t *)(p) + 1) << 0;
}
#endif

__STATIC_FORCEINLINE
uint16_t ntoh16(const void *p)
{
    return (uint16_t) * ((const uint8_t *)(p) + 0) << 8 |
           (uint16_t) * ((const uint8_t *)(p) + 1) << 0;
}

__STATIC_FORCEINLINE
uint32_t ntoh32(const void *p)
{
    return (uint32_t) * ((const uint8_t *)(p) + 0) << 24 |
           (uint32_t) * ((const uint8_t *)(p) + 1) << 16 |
           (uint32_t) * ((const uint8_t *)(p) + 2) << 8  |
           (uint32_t) * ((const uint8_t *)(p) + 3) << 0;
}

__STATIC_FORCEINLINE
uint64_t ntoh64(const void *p)
{
    return (uint64_t) * ((const uint8_t *)(p) + 0) << 56 |
           (uint64_t) * ((const uint8_t *)(p) + 1) << 48 |
           (uint64_t) * ((const uint8_t *)(p) + 2) << 40 |
           (uint64_t) * ((const uint8_t *)(p) + 3) << 32 |
           (uint64_t) * ((const uint8_t *)(p) + 4) << 24 |
           (uint64_t) * ((const uint8_t *)(p) + 5) << 16 |
           (uint64_t) * ((const uint8_t *)(p) + 6) << 8  |
           (uint64_t) * ((const uint8_t *)(p) + 7) << 0;
}

#endif /* __INET_H */

