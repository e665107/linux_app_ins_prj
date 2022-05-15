
#ifndef __FIFO_H
#define __FIFO_H

#include "constant_ops.h"

struct __kfifo
{
    unsigned int in;
    unsigned int out;
    unsigned int mask;
    unsigned int esize;
    void         *data;
};

#define __STRUCT_KFIFO_COMMON(datatype, recsize, ptrtype)                      \
    union {                                                                    \
        struct __kfifo  kfifo;                                                 \
        datatype        *type;                                                 \
        const datatype  *const_type;                                           \
        char            (*rectype)[recsize];                                   \
        ptrtype         *ptr;                                                  \
        ptrtype const   *ptr_const;                                            \
    }

#define __STRUCT_KFIFO_PTR(type, recsize, ptrtype)                             \
    {                                                                          \
        __STRUCT_KFIFO_COMMON(type, recsize, ptrtype);                         \
        type        buf[0];                                                    \
    }

#define STRUCT_KFIFO_PTR(type)                                                 \
    struct __STRUCT_KFIFO_PTR(type, 0, type)

#define __STRUCT_KFIFO(type, size, recsize, ptrtype)                           \
    {                                                                          \
        __STRUCT_KFIFO_COMMON(type, recsize, ptrtype);                         \
        type        buf[((size < 2) || (size & (size - 1))) ? -1 : size];      \
    }

#define STRUCT_KFIFO(type, size)                                               \
    struct __STRUCT_KFIFO(type, size, 0, type)

#define STRUCT_KFIFO_PTR(type)                                                 \
    struct __STRUCT_KFIFO_PTR(type, 0, type)

/**
 * DECLARE_KFIFO - macro to declare a fifo object
 *   @fifo: name of the declared fifo
 *   @type: type of the fifo elements
 *   @size: the number of elements in the fifo, this must be a power of 2
 */
#define DECLARE_KFIFO(fifo, type, size) STRUCT_KFIFO(type, size) fifo

/**
 * INIT_KFIFO - Initialize a fifo declared by DECLARE_KFIFO
 *   @fifo: name of the declared fifo datatype
 */
#define INIT_KFIFO(fifo)                                                       \
    (void)({                                                                   \
        typeof(&(fifo)) __tmp = &(fifo);                                       \
        struct __kfifo *__kfifo = &__tmp->kfifo;                               \
        __kfifo->in    = 0;                                                    \
        __kfifo->out   = 0;                                                    \
        __kfifo->mask  = ARRAY_SIZE(__tmp->buf) - 1;                           \
        __kfifo->esize = sizeof(*__tmp->buf);                                  \
        __kfifo->data  = __tmp->buf;                                           \
    })

/**
 * kfifo_len - returns the number of used elements in the fifo
 *   @fifo: address of the fifo to be used
 */
#define kfifo_len(fifo)                                                        \
    ({                                                                         \
        typeof((fifo) + 1) __tmpl = (fifo);                                    \
        __tmpl->kfifo.in - __tmpl->kfifo.out;                                  \
    })

/**
 * kfifo_is_empty - returns true if the fifo is empty
 *   @fifo: address of the fifo to be used
 */
#define kfifo_is_empty(fifo)                                                   \
    ({                                                                         \
        typeof((fifo) + 1) __tmpq = (fifo);                                    \
        __tmpq->kfifo.in == __tmpq->kfifo.out;                                 \
    })

/**
 * kfifo_is_full - returns true if the fifo is full
 *   @fifo: address of the fifo to be used
 */
#define kfifo_is_full(fifo)                                                    \
    ({                                                                         \
        typeof((fifo) + 1) __tmpq = (fifo);                                    \
        kfifo_len(__tmpq) > __tmpq->kfifo.mask;                                \
    })

/**
 * kfifo_put - put data into the fifo
 *   @fifo: address of the fifo to be used
 *   @val: the data to be added
 *
 * This macro copies the given value into the fifo.
 * It returns 0 if the fifo was full. Otherwise it returns the number
 * processed elements.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these macro.
 */
#define kfifo_put_nosafe(fifo, val)                                            \
    ({                                                                         \
        typeof((fifo) + 1) __tmp = (fifo);                                     \
        typeof(*__tmp->const_type) __val = (val);                              \
        struct __kfifo *__kfifo = &__tmp->kfifo;                               \
        (__tmp->buf)[__kfifo->in & __tmp->kfifo.mask] =                        \
                *(typeof(__tmp->type))&__val;                                  \
        __kfifo->in++;                                                         \
    })

#define kfifo_put(fifo, val)                                                   \
    ({                                                                         \
        typeof((fifo) + 1) __tmp = (fifo);                                     \
        typeof(*__tmp->const_type) __val = (val);                              \
        unsigned int __ret;                                                    \
        struct __kfifo *__kfifo = &__tmp->kfifo;                               \
        __ret = !kfifo_is_full(__tmp);                                         \
        if (__ret) {                                                           \
            (__tmp->buf)[__kfifo->in & __tmp->kfifo.mask] =                    \
                    *(typeof(__tmp->type))&__val;                              \
            __kfifo->in++;                                                     \
        }                                                                      \
        __ret;                                                                 \
    })

/**
 * kfifo_get - get data from the fifo
 *   @fifo: address of the fifo to be used
 *   @val: address where to store the data
 *
 * This macro reads the data from the fifo.
 * It returns 0 if the fifo was empty. Otherwise it returns the number
 * processed elements.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these macro.
 */
#define kfifo_get(fifo, val)                                                   \
    ({                                                                         \
        typeof((fifo) + 1) __tmp = (fifo);                                     \
        typeof(__tmp->ptr) __val = (val);                                      \
        unsigned int __ret;                                                    \
        struct __kfifo *__kfifo = &__tmp->kfifo;                               \
        __ret = !kfifo_is_empty(__tmp);                                        \
        if (__ret) {                                                           \
            *(typeof(__tmp->type))__val =                                      \
                    (__tmp->buf)[__kfifo->out & __tmp->kfifo.mask];            \
            __kfifo->out++;                                                    \
        }                                                                      \
        __ret;                                                                 \
    })


/**
 * kfifo_peek - get data from the fifo without removing
 * @fifo: address of the fifo to be used
 * @val: address where to store the data
 *
 * This reads the data from the fifo without removing it from the fifo.
 * It returns 0 if the fifo was empty. Otherwise it returns the number
 * processed elements.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these macro.
 */
#define kfifo_peek(fifo, val)                                                  \
    ({                                                                         \
        typeof((fifo) + 1) __tmp = (fifo);                                     \
        typeof(__tmp->ptr) __val = (val);                                      \
        unsigned int __ret;                                                    \
        struct __kfifo *__kfifo = &__tmp->kfifo;                               \
        __ret = !kfifo_is_empty(__tmp);                                        \
        if (__ret) {                                                           \
            *(typeof(__tmp->type))__val =                                      \
                    (__tmp->buf)[__kfifo->out & __tmp->kfifo.mask];            \
        }                                                                      \
        __ret;                                                                 \
    })


/**
 * kfifo_prepare - get in address from the fifo without removing
 * @fifo: address of the fifo to be used
 * @val: address where to store the data
 */
#define kfifo_prepare(fifo, val)                                               \
    ({                                                                         \
        unsigned int __ret;                                                    \
        __ret;                                                                 \
    })

/**
 * kfifo_skip_in/kfifo_skip_out - skip in/output data
 * @fifo: address of the fifo to be used
 */
#define kfifo_skip_in(fifo)                                                    \
    ({                                                                         \
        typeof((fifo) + 1) __tmp = (fifo);                                     \
        __tmp->kfifo.in++;                                                     \
    })
#define kfifo_skip_out(fifo)                                                   \
    ({                                                                         \
        typeof((fifo) + 1) __tmp = (fifo);                                     \
        __tmp->kfifo.out++;                                                    \
    })

/**
 * kfifo_poke_in/kfifo_poke_out
 */
#define kfifo_poke_in(fifo)                                                    \
    ({                                                                         \
        typeof((fifo) + 1) __tmp = (fifo);                                     \
        __tmp->kfifo.in & __tmp->kfifo.mask;                                   \
    })
#define kfifo_poke_out(fifo)                                                   \
    ({                                                                         \
        typeof((fifo) + 1) __tmp = (fifo);                                     \
        __tmp->kfifo.out & __tmp->kfifo.mask;                                  \
    })

#endif

