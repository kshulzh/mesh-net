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

#include <stdint.h>
#include "containers/array.h"
#include "utils/predicate.h"
#include "utils/malloc.h"

ARRAY(short)
ARRAY(int)
ARRAY(long)

typedef unsigned int uint32_t;
typedef struct {
    uint32_t size;
    char *start;
    char *temp;
    char *end;
    char is_locked;
} buffer;

#define buffer(name, size) \
char name##_array[size]; \
buffer *name = new_buffer(name##_array, size); \

#define clone_declaration(type) void * type##_clone(void *src);

#define clone(type) void * type##_clone(void *src) { \
   void *dest = mem_alloc(sizeof(type));    \
   mem_copy(dest,src, sizeof(type));                 \
   return dest;                                                      \
}                                           \


void *empty_clone(void *);

void buffer_init(buffer *buf, uint32_t size, char *arr);

char *write_to_buffer(buffer *buf, void *data, uint32_t size);

char *read_from_buffer(buffer *buf, uint32_t size);

char *mem_copy(char *dest, const char *src, uint32_t size);

void buffer_reset(buffer *buf);

char buffer_predicate_is_locked(void *thiz, void *params);

buffer *new_buffer(char *data, unsigned int size);

predicate *buffer_is_locked();

predicate *buffer_is_free();

char *write_char_to_buffer(buffer *buf, char d);

char *write_short_to_buffer(buffer *buf, short d);

char *write_int_to_buffer(buffer *buf, int d);

char *write_long_to_buffer(buffer *buf, long d);


char read_char_from_buffer(buffer *buf);

short read_short_from_buffer(buffer *buf);

int read_int_from_buffer(buffer *buf);

long read_long_from_buffer(buffer *buf);

#endif //MESH_NET_BUFFER_H
