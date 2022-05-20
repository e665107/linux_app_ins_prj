#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include "priv.h"
#include <stdio.h>

/*******************************************************************************
 * types.h
 ******************************************************************************/
struct hlist_node
{
    struct hlist_node *next, **pprev;
};

struct hlist_head
{
    struct hlist_node *first;
};

/*******************************************************************************
 * list.h
 ******************************************************************************/
#define HLIST_HEAD_INIT { .first = NULL }
__STATIC_FORCEINLINE
void INIT_HLIST_NODE(struct hlist_node *h)
{
    h->next = NULL;
    h->pprev = NULL;
}

__STATIC_FORCEINLINE
int hlist_unhashed(const struct hlist_node *h)
{
    return !h->pprev;
}

__STATIC_FORCEINLINE
void __hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **pprev = n->pprev;

    WRITE_ONCE(*pprev, next);
    if (next)
        next->pprev = pprev;
}

__STATIC_FORCEINLINE
void hlist_del_init(struct hlist_node *n)
{
    if (!hlist_unhashed(n))
    {
        __hlist_del(n);
        INIT_HLIST_NODE(n);
    }
}

/* hlist_add_head - add a new entry at the beginning of the hlist
 * @n: new entry to be added
 * @h: hlist head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks. */
__STATIC_FORCEINLINE
void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    struct hlist_node *first = h->first;
    n->next = first;
    if (first)
        first->pprev = &n->next;
    h->first = n;
    n->pprev = &h->first;
}

#define hlist_entry(ptr, type, member) container_of(ptr,type,member)

#define hlist_entry_safe(ptr, type, member)                     \
    ({ typeof(ptr) ____ptr = (ptr);                             \
        ____ptr ? hlist_entry(____ptr, type, member) : NULL;    \
    })

/* hlist_for_each_entry - iterate over list of given type
*   @pos:    the type * to use as a loop cursor.
*   @head:   the head for your list.
*   @member: the name of the hlist_node within the struct. */
#define hlist_for_each_entry(pos, head, member)                         \
    for (pos = hlist_entry_safe((head)->first, typeof(*(pos)), member); \
         pos;                                                           \
         pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))

/*******************************************************************************
 * hash.h
 ******************************************************************************/
#if __RISCV_XLEN == 32
#define GOLDEN_RATIO_PRIME GOLDEN_RATIO_32
#define hash_long(val, bits) hash_32(val, bits)
#elif __RISCV_XLEN == 64
#define hash_long(val, bits) hash_64(val, bits)
#define GOLDEN_RATIO_PRIME GOLDEN_RATIO_64
#else
#error Wordsize not 32 or 64
#endif

#define GOLDEN_RATIO_32 0x61C88647
#define GOLDEN_RATIO_64 0x61C8864680B583EBull

#ifndef HAVE_ARCH__HASH_32
#define __hash_32 __hash_32_generic
#endif
__STATIC_FORCEINLINE
uint32_t __hash_32_generic(uint32_t val)
{
    return val * GOLDEN_RATIO_32;
}

#ifndef HAVE_ARCH_HASH_32
#define hash_32 hash_32_generic
#endif
__STATIC_FORCEINLINE
uint32_t hash_32_generic(uint32_t val, unsigned int bits)
{
    /* High bits are more random, so use them. */
    return __hash_32(val) >> (32 - bits);
}

#ifndef HAVE_ARCH_HASH_64
#define hash_64 hash_64_generic
#endif
__STATIC_FORCEINLINE
uint32_t hash_64_generic(uint64_t val, unsigned int bits)
{
#if __RISCV_XLEN == 64
    /* 64x64-bit multiply is efficient on all 64-bit processors */
    return val * GOLDEN_RATIO_64 >> (64 - bits);
#else
    /* Hash 64 bits using only 32x32-bit multiply. */
    return hash_32((uint32_t)val ^ __hash_32(val >> 32), bits);
#endif
}

/*******************************************************************************
 * hashtable.h
 ******************************************************************************/
#define DEFINE_HASHTABLE(name, bits)                    \
    struct hlist_head name[1 << (bits)] =               \
    { [0 ... ((1 << (bits)) - 1)] = HLIST_HEAD_INIT }

#define HASH_SIZE(name) (ARRAY_SIZE(name))
#define HASH_BITS(name) ilog2(HASH_SIZE(name))

/* Use hash_32 when possible to allow for fast 32bit hashing in 64bit kernels */
#define hash_min(val, bits)                                             \
    (sizeof(val) <= 4 ? hash_32(val, bits) : hash_long(val, bits))

#define hash_add(hashtable, node, key)                                  \
    hlist_add_head(node, &hashtable[hash_min(key, HASH_BITS(hashtable))])

/**
 * hash_del - remove an object from a hashtable
 * @node: &struct hlist_node of the object to remove
 */
__STATIC_FORCEINLINE
void hash_del(struct hlist_node *node)
{
    hlist_del_init(node);
}

/* hash_for_each_possible - iterate over all possible objects hashing to the
 * same bucket
 *   @name: hashtable to iterate
 *   @obj: the type * to use as a loop cursor for each entry
 *   @member: the name of the hlist_node within the struct
 *   @key: the key of the objects to iterate over */
#define hash_for_each_possible(name, obj, member, key)                  \
    hlist_for_each_entry(obj, &name[hash_min(key, HASH_BITS(name))], member)



#endif
