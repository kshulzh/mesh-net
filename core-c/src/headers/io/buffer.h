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

#ifndef MESH_NET_BUFFER_H
#define MESH_NET_BUFFER_H

#include "containers/array.h"
ARRAY(char)
ARRAY(short)
ARRAY(int)
ARRAY(long)

typedef unsigned int uint32_t;
struct buffer {
    uint32_t size;
    char *start;
    char *temp;
    char *end;
};

typedef struct buffer buffer;

void buffer_init(buffer *buf, uint32_t size, char *arr);

char * write_to_buffer(buffer *buf, void *data, uint32_t size);

char * read_from_buffer(buffer *buf, uint32_t size);

char * mem_copy(char *dest,const char * src, uint32_t size);

#endif //MESH_NET_BUFFER_H
