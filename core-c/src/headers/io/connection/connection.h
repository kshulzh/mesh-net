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

#ifndef MESH_NET_CONNECTION_H
#define MESH_NET_CONNECTION_H

#include "radar.h"

typedef struct {
    device d;
    radar *r;

    void (*open)(void *thiz);

    void (*close)(void *thiz);

    char (*is_connected)(void *thiz);

    int32_t (*read_array)(void *thiz, uint8_t [], uint32_t, uint32_t);

    int32_t (*write_array)(void *thiz, uint8_t [], uint32_t);

    void *(*get_properties)(void *thiz);

    void (*set_properties)(void *thiz, void *);
} connection;

predicate *connection_device_by_id(uint64_t id);

#endif //MESH_NET_CONNECTION_H
