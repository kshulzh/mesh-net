/*
 * Copyright (c) 2023. Kirill Shulzhenko
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

#ifndef MESH_NET_CONNECTED_DEVICE_H
#define MESH_NET_CONNECTED_DEVICE_H

#include "../containers/array.h"
#include "device.h"
#include "../io/connection/connection.h"
ARRAY(connection)

typedef struct {
    device device;
    list connections;
} connected_device;

#endif //MESH_NET_CONNECTED_DEVICE_H
