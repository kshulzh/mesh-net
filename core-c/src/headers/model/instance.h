/*
 * Copyright (c) 2023-2024. Kirill Shulzhenko
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MESH_NET_INSTANCE_H
#define MESH_NET_INSTANCE_H

#include "containers/list.h"
#include "devices/device.h"
#include "io/connection/radar.h"
#include "graph.h"

typedef struct {
    list radars;
    list devices;
    list buffers;
    list connections;
    list buffered_connections;
    device this_device;
    graph *g;
} instance;

instance *new_instance(device *d);

void instance_run(instance *inst);

void instance_add_radar(instance *inst, void *r);

#endif //MESH_NET_INSTANCE_H
