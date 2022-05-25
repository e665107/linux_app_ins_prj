
#ifndef _IN_CKSUM_H
#define _IN_CKSUM_H

#include <nmsis_core.h>
#include <stdint.h>

#define NIC_RX_TCP_CHKSUM ((uint32_t)0x1)
#define NIC_RX_UDP_CHKSUM ((uint32_t)0x2)

typedef struct
{
    const uint8_t *ptr;
    uint32_t len;
} VecTypeDef;

#define SET_CKSUM_VEC_PTR(vecelem, data, length)                               \
    ({                                                                             \
        vecelem.ptr = (data);                                                      \
        vecelem.len = (length);                                                    \
    })

#define ADDCARRY(x)  {if ((x) > 65535) (x) -= 65535;}
#define REDUCE {l_util.l = sum; sum = l_util.s[0] + l_util.s[1]; ADDCARRY(sum);}

__STATIC_FORCEINLINE
int inCksum(const VecTypeDef *vec, int veclen)
{
    register const uint16_t *w;
    register int sum = 0;
    register int mlen = 0;
    int byte_swapped = 0;

    union
    {
        uint8_t c[2];
        uint16_t s;
    } s_util;
    union
    {
        uint16_t s[2];
        uint32_t l;
    } l_util;

    for (; veclen != 0; vec++, veclen--)
    {
        if (vec->len == 0)
            continue;
        w = (const uint16_t *)(const void *)vec->ptr;
        if (mlen == -1)
        {
            /*
             * The first byte of this chunk is the continuation
             * of a word spanning between this chunk and the
             * last chunk.
             *
             * s_util.c[0] is already saved when scanning previous
             * chunk.
             */
            s_util.c[1] = *(const uint8_t *)w;
            sum += s_util.s;
            w = (const uint16_t *)(const void *)((const uint8_t *)w + 1);
            mlen = vec->len - 1;
        }
        else
            mlen = vec->len;
        /*
         * Force to even boundary.
         */
        if ((1 & (intptr_t)w) && (mlen > 0))
        {
            REDUCE;
            sum <<= 8;
            s_util.c[0] = *(const uint8_t *)w;
            w = (const uint16_t *)(const void *)((const uint8_t *)w + 1);
            mlen--;
            byte_swapped = 1;
        }
        /*
         * Unroll the loop to make overhead from
         * branches &c small.
         */
        while ((mlen -= 32) >= 0)
        {
            sum += w[0];
            sum += w[1];
            sum += w[2];
            sum += w[3];
            sum += w[4];
            sum += w[5];
            sum += w[6];
            sum += w[7];
            sum += w[8];
            sum += w[9];
            sum += w[10];
            sum += w[11];
            sum += w[12];
            sum += w[13];
            sum += w[14];
            sum += w[15];
            w += 16;
        }
        mlen += 32;
        while ((mlen -= 8) >= 0)
        {
            sum += w[0];
            sum += w[1];
            sum += w[2];
            sum += w[3];
            w += 4;
        }
        mlen += 8;
        if (mlen == 0 && byte_swapped == 0)
            continue;
        REDUCE;
        while ((mlen -= 2) >= 0)
        {
            sum += *w++;
        }
        if (byte_swapped)
        {
            REDUCE;
            sum <<= 8;
            byte_swapped = 0;
            if (mlen == -1)
            {
                s_util.c[1] = *(const uint8_t *)w;
                sum += s_util.s;
                mlen = 0;
            }
            else
                mlen = -1;
        }
        else if (mlen == -1)
            s_util.c[0] = *(const uint8_t *)w;
    }
    if (mlen == -1)
    {
        /* The last mbuf has odd # of bytes. Follow the
           standard (the odd byte may be shifted left by 8 bits
           or not as determined by endian-ness of the machine) */
        s_util.c[1] = 0;
        sum += s_util.s;
    }
    REDUCE;
    return (~sum & 0xffff);
}

#endif /* _IN_CKSUM_H */



