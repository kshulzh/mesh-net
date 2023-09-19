//
// Created by kirill on 18.09.23.
//

#ifndef MESH_NET_INSTANCE_H
#define MESH_NET_INSTANCE_H

#include "containers/list.h"
#include "devices/device.h"

typedef struct {
    list radars;
    list devices;
    list buffers;
    list connections;
    device this_device;
} instance;



#endif //MESH_NET_INSTANCE_H
