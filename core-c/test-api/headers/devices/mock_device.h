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

#ifndef MESH_NET_MOCK_DEVICE_H
#define MESH_NET_MOCK_DEVICE_H

#include "model/instance.h"
#include "io/connection/mock_connection.h"
#include "io/connection/mock_radar.h"

typedef struct {
    device d;
    instance inst;
} mock_device;

mock_device *new_mock_device(device *d);

void mock_device_link(mock_device *md1, mock_device *md2);

void mock_device_find(mock_device *md);

#endif //MESH_NET_MOCK_DEVICE_H
