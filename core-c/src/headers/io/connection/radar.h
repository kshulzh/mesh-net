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

#ifndef MESH_NET_RADAR_H
#define MESH_NET_RADAR_H

#include "model/instance.h"

typedef struct {
    void *inst;
    list connections;

    void (*start)(void *thiz);

    void (*stop)(void *thiz);

    void (*scan)(void *thiz);

    char (*is_running)(void *thiz);

    void (*set_properties)(void *thiz, void *);

    void *(*get_properties)(void *thiz);

    void (*on_find_device_handler)(void *thiz, void *);
} radar;


#endif //MESH_NET_RADAR_H
