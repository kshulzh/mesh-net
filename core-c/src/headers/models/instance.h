//
// Created by kirill on 18.09.23.
//

#ifndef MESH_NET_INSTANCE_H
#define MESH_NET_INSTANCE_H

#include "containers/list.h"
#include "devices/device.h"
#include "io/connection/radar.h"

typedef struct {
    list radars;
    list devices;
    list buffers;
    list buffered_connections;
    device this_device;
} instance;

instance *new_instance(device*d) {
    instance* i = New(instance);
    i->this_device = *d;
    return i;
}

void instance_run(instance * inst);

#endif //MESH_NET_INSTANCE_H
