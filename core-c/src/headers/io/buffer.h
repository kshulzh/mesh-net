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

typedef struct {
    uint32_t size;
    char *start;
    char *temp;
    char *end;
    char is_locked;
} buffer;

#define buffer(name, size) \
char name##_array[size]; \
buffer *name = new_buffer((uint8_t*)name##_array, size); \

#define clone_declaration(type) void * type##_clone(void *src);

#define clone(type) void * type##_clone(void *src) { \
   void *dest = mem_alloc(sizeof(type));    \
   mem_copy(dest,src, sizeof(type));                 \
   return dest;                                                      \
}                                           \


void *empty_clone(void *);

void buffer_init(buffer *buf, uint32_t size, uint8_t  *arr);

char *write_to_buffer(buffer *buf, void *data, uint32_t size);

char *read_from_buffer(buffer *buf, uint32_t size);

char *mem_copy(uint8_t *dest, const uint8_t *src, uint32_t size);

void buffer_reset(buffer *buf);

char buffer_predicate_is_locked(void *thiz, void *params);

buffer *new_buffer(uint8_t *data, uint32_t size);

predicate *buffer_is_locked();

predicate *buffer_is_free();

char *write_char_to_buffer(buffer *buf, uint8_t d);

char *write_short_to_buffer(buffer *buf, uint16_t d);

char *write_int_to_buffer(buffer *buf, uint32_t d);

char *write_long_to_buffer(buffer *buf, uint64_t d);


uint8_t read_char_from_buffer(buffer *buf);

uint16_t read_short_from_buffer(buffer *buf);

uint32_t read_int_from_buffer(buffer *buf);

uint64_t read_long_from_buffer(buffer *buf);

uint64_t read_number(uint8_t* ptr,uint8_t size);

void write_number(uint8_t* ptr, uint64_t num, uint8_t size);

void * read_dump_and_get(buffer *buf, uint32_t size);

void write_dump(buffer *buf,void* o, uint32_t size);



#endif //MESH_NET_BUFFER_H
