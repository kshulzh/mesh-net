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

#ifndef MESH_NET_MOCK_RADAR_H
#define MESH_NET_MOCK_RADAR_H

#include "devices/device.h"
#include "io/connection/radar.h"
#include "containers/list.h"

typedef struct {
    radar r;
    char is_running;
    list queue;
    void (*on_find_device_handler)(void *thiz,void *);

} mock_radar;

void mock_radar_start(void *thiz);

void mock_radar_stop(void *thiz);


char mock_radar_is_started(void *thiz);


void mock_radar_set_properties(void *thiz, void *);


void *mock_radar_get_properties(void *thiz);


void mock_on_find_device_handler(void *thiz, void (*on_find_device_handler)(void *thiz,void *));
radar* new_mock_radar();

void mock_radar_find(void *thiz);
void mock_radar_add_to_queue(void *thiz,void *d);
#endif //MESH_NET_MOCK_RADAR_H
