
#ifndef __CONSTANT_OPS_H
#define __CONSTANT_OPS_H

#include <nmsis_core.h>
#include <string.h>
#include <stdio.h>

/*  */
#define SET_FIELD(flags, val, bitpos, mask)                                    \
    (flags) =                                                           \
            (((flags) & (~((mask) << (bitpos)))) | (((val) & (mask)) << (bitpos)))
#define GET_FIELD(flags, bitpos, mask) (((flags) >> (bitpos)) & (mask))

#define SET_FLAG(flags, bitpos)   (flags) = ((flags) | (1 << (bitpos)))
#define CLEAR_FLAG(flags, bitpos) (flags) = ((flags) & (~(1 << (bitpos))))
#define GET_FLAG(flags, bitpos)   (((flags) >> (bitpos)) & 1)

/*  */
#undef WRITE_ONCE
#define WRITE_ONCE(var, val)                            \
    (*((volatile typeof(val) *)(&(var))) = (val))

#undef ARRAY_SIZE
#define ARRAY_SIZE(arr)                         \
    (sizeof(arr) / sizeof((arr)[0]))

#undef offsetof
#define offsetof(TYPE, MEMBER)                  \
    ((size_t)&((TYPE *)0)->MEMBER)

#undef container_of
#define container_of(ptr, type, member)                 \
    ((type *)((void *)(ptr) - offsetof(type, member)))

#if 0
/*  */
__STATIC_FORCEINLINE
int ilog2(unsigned long v)
{
    int l = 0;
    while ((1UL << l) < v)
        l++;
    return l;
}
/**
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
__STATIC_FORCEINLINE int fls(unsigned int x)
{
    int r = 32;

    if (!x)
        return 0;
    if (!(x & 0xffff0000u))
    {
        x <<= 16;
        r -= 16;
    }
    if (!(x & 0xff000000u))
    {
        x <<= 8;
        r -= 8;
    }
    if (!(x & 0xf0000000u))
    {
        x <<= 4;
        r -= 4;
    }
    if (!(x & 0xc0000000u))
    {
        x <<= 2;
        r -= 2;
    }
    if (!(x & 0x80000000u))
    {
        x <<= 1;
        r -= 1;
    }
    return r;
}
#else

/**
 * __fls - find last (most-significant) set bit in a long word
 * @word: the word to search
 *
 * Undefined if no set bit exists, so code should check against 0 first.
 */
__STATIC_FORCEINLINE unsigned long __fls(unsigned long word)
{
    int num = __RISCV_XLEN - 1;

#if __RISCV_XLEN == 64
    if (!(word & (~0ul << 32)))
    {
        num -= 32;
        word <<= 32;
    }
#endif
    if (!(word & (~0ul << (__RISCV_XLEN - 16))))
    {
        num -= 16;
        word <<= 16;
    }
    if (!(word & (~0ul << (__RISCV_XLEN - 8))))
    {
        num -= 8;
        word <<= 8;
    }
    if (!(word & (~0ul << (__RISCV_XLEN - 4))))
    {
        num -= 4;
        word <<= 4;
    }
    if (!(word & (~0ul << (__RISCV_XLEN - 2))))
    {
        num -= 2;
        word <<= 2;
    }
    if (!(word & (~0ul << (__RISCV_XLEN - 1))))
        num -= 1;
    return num;
}

/**
 * fls64 - find last set bit in a 64-bit word
 * @x: the word to search
 *
 * This is defined in a similar way as the libc and compiler builtin
 * ffsll, but returns the position of the most significant set bit.
 *
 * fls64(value) returns 0 if value is 0 or the position of the last
 * set bit if value is nonzero. The last (most significant) bit is
 * at position 64.
 */
#if __RISCV_XLEN == 32
__STATIC_FORCEINLINE int fls64(uint64_t x)
{
    uint32_t h = x >> 32;
    if (h)
        return fls(h) + 32;
    return fls(x);
}
#elif __RISCV_XLEN == 64
__STATIC_FORCEINLINE int fls64(uint64_t x)
{
    if (x == 0)
        return 0;
    return __fls(x) + 1;
}
#else
#error __RISCV_XLEN not 32 or 64
#endif

/*
 * non-constant log of base 2 calculators
 * - the arch may override these in asm/bitops.h if they can be implemented
 *   more efficiently than using fls() and fls64()
 * - the arch is not required to handle n==0 if implementing the fallback
 */
static inline __attribute__((const))
int __ilog2_u32(uint32_t n)
{
    return fls(n) - 1;
}

static inline __attribute__((const))
int __ilog2_u64(uint64_t n)
{
    return fls64(n) - 1;
}

/**
 * const_ilog2 - log base 2 of 32-bit or a 64-bit constant unsigned value
 * @n: parameter
 *
 * Use this where sparse expects a true constant expression, e.g. for array
 * indices.
 */
#define const_ilog2(n)                                                         \
    (                                                                          \
            __builtin_constant_p(n) ? (                                        \
                    (n) < 2 ? 0 :                                              \
                    (n) & (1ULL << 63) ? 63 :                                  \
                    (n) & (1ULL << 62) ? 62 :                                  \
                    (n) & (1ULL << 61) ? 61 :                                  \
                    (n) & (1ULL << 60) ? 60 :                                  \
                    (n) & (1ULL << 59) ? 59 :                                  \
                    (n) & (1ULL << 58) ? 58 :                                  \
                    (n) & (1ULL << 57) ? 57 :                                  \
                    (n) & (1ULL << 56) ? 56 :                                  \
                    (n) & (1ULL << 55) ? 55 :                                  \
                    (n) & (1ULL << 54) ? 54 :                                  \
                    (n) & (1ULL << 53) ? 53 :                                  \
                    (n) & (1ULL << 52) ? 52 :                                  \
                    (n) & (1ULL << 51) ? 51 :                                  \
                    (n) & (1ULL << 50) ? 50 :                                  \
                    (n) & (1ULL << 49) ? 49 :                                  \
                    (n) & (1ULL << 48) ? 48 :                                  \
                    (n) & (1ULL << 47) ? 47 :                                  \
                    (n) & (1ULL << 46) ? 46 :                                  \
                    (n) & (1ULL << 45) ? 45 :                                  \
                    (n) & (1ULL << 44) ? 44 :                                  \
                    (n) & (1ULL << 43) ? 43 :                                  \
                    (n) & (1ULL << 42) ? 42 :                                  \
                    (n) & (1ULL << 41) ? 41 :                                  \
                    (n) & (1ULL << 40) ? 40 :                                  \
                    (n) & (1ULL << 39) ? 39 :                                  \
                    (n) & (1ULL << 38) ? 38 :                                  \
                    (n) & (1ULL << 37) ? 37 :                                  \
                    (n) & (1ULL << 36) ? 36 :                                  \
                    (n) & (1ULL << 35) ? 35 :                                  \
                    (n) & (1ULL << 34) ? 34 :                                  \
                    (n) & (1ULL << 33) ? 33 :                                  \
                    (n) & (1ULL << 32) ? 32 :                                  \
                    (n) & (1ULL << 31) ? 31 :                                  \
                    (n) & (1ULL << 30) ? 30 :                                  \
                    (n) & (1ULL << 29) ? 29 :                                  \
                    (n) & (1ULL << 28) ? 28 :                                  \
                    (n) & (1ULL << 27) ? 27 :                                  \
                    (n) & (1ULL << 26) ? 26 :                                  \
                    (n) & (1ULL << 25) ? 25 :                                  \
                    (n) & (1ULL << 24) ? 24 :                                  \
                    (n) & (1ULL << 23) ? 23 :                                  \
                    (n) & (1ULL << 22) ? 22 :                                  \
                    (n) & (1ULL << 21) ? 21 :                                  \
                    (n) & (1ULL << 20) ? 20 :                                  \
                    (n) & (1ULL << 19) ? 19 :                                  \
                    (n) & (1ULL << 18) ? 18 :                                  \
                    (n) & (1ULL << 17) ? 17 :                                  \
                    (n) & (1ULL << 16) ? 16 :                                  \
                    (n) & (1ULL << 15) ? 15 :                                  \
                    (n) & (1ULL << 14) ? 14 :                                  \
                    (n) & (1ULL << 13) ? 13 :                                  \
                    (n) & (1ULL << 12) ? 12 :                                  \
                    (n) & (1ULL << 11) ? 11 :                                  \
                    (n) & (1ULL << 10) ? 10 :                                  \
                    (n) & (1ULL <<  9) ?  9 :                                  \
                    (n) & (1ULL <<  8) ?  8 :                                  \
                    (n) & (1ULL <<  7) ?  7 :                                  \
                    (n) & (1ULL <<  6) ?  6 :                                  \
                    (n) & (1ULL <<  5) ?  5 :                                  \
                    (n) & (1ULL <<  4) ?  4 :                                  \
                    (n) & (1ULL <<  3) ?  3 :                                  \
                    (n) & (1ULL <<  2) ?  2 :                                  \
                    1) :                                                       \
            -1)


/**
 * ilog2 - log base 2 of 32-bit or a 64-bit unsigned value
 * @n: parameter
 *
 * constant-capable log of base 2 calculation
 * - this can be used to initialise global variables from constant data, hence
 * the massive ternary operator construction
 *
 * selects the appropriately-sized optimised version depending on sizeof(n)
 */
#define ilog2(n)                                                               \
    (                                                                          \
            __builtin_constant_p(n) ?                                          \
            const_ilog2(n) :                                                   \
            (sizeof(n) <= 4) ?                                                 \
            __ilog2_u32(n) :                                                   \
            __ilog2_u64(n)                                                     \
    )
#endif

/*  */
__STATIC_FORCEINLINE
void DUMPL(const char *var,
           const uint8_t p[], uint32_t l)
{
    int i;

    printf("%s: length %u, address %p", var, l, p);
    if (NULL != p && l > 0)
    {
        for (i = 0; i < l; i++)
        {
            if (i % 16 == 0)
                printf("\n");
            else if (i % 8 == 0)
                printf("- ");
            printf("%02x ", p[i]);
        }
    }
    printf("\n");
    return;
}

#endif /* __CONSTANT_OPS_H */
