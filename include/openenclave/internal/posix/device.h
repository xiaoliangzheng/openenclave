// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef _OE_DEVICE_H
#define _OE_DEVICE_H

#include <openenclave/bits/result.h>
#include <openenclave/internal/posix/devicetypes.h>
#include <openenclave/internal/posix/epoll_ops.h>
#include <openenclave/internal/posix/eventfd_ops.h>
#include <openenclave/internal/posix/fd.h>
#include <openenclave/internal/posix/fs_ops.h>
#include <openenclave/internal/posix/sock_ops.h>

OE_EXTERNC_BEGIN

typedef struct _oe_device oe_device_t;

struct _oe_device
{
    /* Type of this device: OE_DEVID_FILE or OE_DEVID_SOCKET. */
    oe_device_type_t type;

    /* Index of the device into the device table. */
    uint64_t devid;

    /* sizeof additional data. To get a pointer to the device private data,
     * ptr = (oe_file_device_t)(devptr+1); usually sizeof(oe_file_t) or
     * sizeof(oe_socket_t).
     */
    size_t size;

    /* String name of this device. */
    const char* devicename;

    union {
        oe_device_ops_t* base;
        oe_fs_ops_t* fs;
        oe_sock_ops_t* socket;
        oe_epoll_ops_t* epoll;
        oe_eventfd_ops_t* eventfd;
    } ops;
};

uint64_t oe_allocate_devid(uint64_t devid);

int oe_release_devid(uint64_t devid);

int oe_set_devid_device(uint64_t devid, oe_device_t* pdevice);

oe_device_t* oe_get_devid_device(uint64_t devid);

int oe_remove_device(uint64_t devid);

OE_EXTERNC_END

#endif // _OE_DEVICE_H
