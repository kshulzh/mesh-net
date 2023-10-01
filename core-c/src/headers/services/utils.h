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

#ifndef MESH_NET_UTILS_H
#define MESH_NET_UTILS_H

#include <stdlib.h>
#include "io/buffer.h"

void buffer_message_set_size(buffer *b);

void free_uint32(void *v);

void *decode_uint32(buffer *b);

void encode_uint32(buffer *b, unsigned int i);

void encode_link(buffer *b, void *l);

void* decode_link(buffer *b);

void *decode_uint64(buffer *b);

#endif //MESH_NET_UTILS_H
