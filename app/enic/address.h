
#ifndef _ADDRESS_H
#define _ADDRESS_H

#include <stdint.h>
#include <assert.h>

#include "priv.h"

typedef enum
{
    AT_NONE,                    /* no link-layer address */
    AT_ETHER,                   /* MAC (Ethernet, 802.x, FDDI) address */
    AT_IPv4,                    /* IPv4 */
    AT_IPv6,                    /* IPv6 */
} Address_TypeTypeDef;

typedef struct
{
    uint32_t type;              /* type of address */
    uint32_t len;               /* length of address, in bytes */
    const void *data;           /* pointer to address data */
    void *priv;
} AddressTypeDef;

__STATIC_FORCEINLINE
void setAddress(AddressTypeDef *addr,
                int addrType,
                int addrLen,
                const void *addrData)
{
#ifdef DEBUG
    if (addrLen == 0)
    {
        /* Zero length must mean no data */
        assert(addrData == NULL);
    }
    else
    {
        /* Must not be AT_NONE - AT_NONE must have no data */
        assert(addrType != AT_NONE);
        /* Make sure we *do* have data */
        assert(addrData != NULL);
    }
#endif
    addr->type = addrType;
    addr->len  = addrLen;
    addr->data = addrData;
    addr->priv = NULL;
    return;
}

#endif /* _FRAME_H */

