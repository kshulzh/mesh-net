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

#ifndef MESH_NET_DEVICE_H
#define MESH_NET_DEVICE_H

#include "utils/new.h"
#include "utils/predicate.h"
#include "io/buffer.h"

typedef struct {
    uint64_t id;
    uint64_t user_id;
} device;

device *new_device(
        uint64_t id,
        uint64_t user_id);

char predicate_device_equals(void *thiz, void *params);

predicate *device_equals(void *thiz);

void encode_device(buffer *b, void *device);

void encode_device_id(buffer *b, void *device);

void *decode_device_id(buffer *b);

void *decode_device(buffer *b);

void free_device(void *);

clone_declaration(device)

#endif //MESH_NET_DEVICE_H
