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
#include "io/buffer.h"
#include "utils/new.h"

extern
void buffer_init(buffer *buf, uint32_t size, uint8_t *arr) {
    buf->size = size;
    buf->start = arr;
    buf->end = arr + size;
    buf->temp = arr;
    buf->is_locked = 0;
}

extern
char *mem_copy(uint8_t *dest, const uint8_t *src, uint32_t size) {
    for (int i = 0; i < size; ++i) {
        dest[i] = src[i];
    }
    return dest;
}

extern
char *write_to_buffer(buffer *buf, void *data, uint32_t size) {
    if (size == 0) {
        return 0;
    }
    //todo case when buffer has noe enough capacity

    char *result = mem_copy(buf->temp, data, size);
    buf->temp += size;
    return result;
}

extern
char *read_from_buffer(buffer *buf, uint32_t size) {
    char *result = buf->temp;
    (buf->temp) += size;
    return result;
}

void buffer_reset(buffer *buf) {
    buf->temp = buf->start;

}

buffer *new_buffer(uint8_t *data, uint32_t size) {
    buffer *b = New(buffer);
    buffer_init(b, size, data);
    return b;
}

char buffer_predicate_is_locked(void *thiz, void *params) {
    buffer *b = (buffer *) thiz;
    return b->is_locked;
}

predicate *BUFFER_IS_LOCKED;
predicate *BUFFER_IS_FREE;

predicate *buffer_is_locked() {
    if (BUFFER_IS_LOCKED == 0) {
        return BUFFER_IS_LOCKED = new_predicate(buffer_predicate_is_locked, 0);
    }
    return BUFFER_IS_LOCKED;
}

char buffer_predicate_is_free(void *thiz, void *params) {
    buffer *b = (buffer *) thiz;
    return 1 - (b->is_locked);
}

predicate *buffer_is_free() {
    if (BUFFER_IS_FREE == 0) {
        return BUFFER_IS_FREE = new_predicate(buffer_predicate_is_free, 0);
    }
    return BUFFER_IS_FREE;
}

void *empty_clone(void *obj) {
    return obj;
}

uint8_t * write_num_to_buffer(buffer *buf,uint64_t d, uint32_t size) {
    uint8_t * res = buf->temp;
    write_number(buf->temp, d, size);
    buf->temp+=size;

    return res;
}


char *write_char_to_buffer(buffer *buf, uint8_t d) {
    return write_num_to_buffer(buf,d,1);
}

char *write_short_to_buffer(buffer *buf, uint16_t d) {
    return write_num_to_buffer(buf,d,2);
}
char *write_int_to_buffer(buffer *buf, uint32_t d) {
    return write_num_to_buffer(buf,d,4);
}
char *write_long_to_buffer(buffer *buf, uint64_t d) {
    return write_num_to_buffer(buf,d,8);
}
uint64_t read_num_from_buffer(buffer *buf, uint32_t size) {
    uint64_t r = read_number(buf->temp,size);
    buf->temp+=size;

    return r;
}
uint8_t read_char_from_buffer(buffer *buf) {
    return read_num_from_buffer(buf, 1);
}

uint16_t read_short_from_buffer(buffer *buf) {
    return read_num_from_buffer(buf, 2);
}
uint32_t read_int_from_buffer(buffer *buf) {
    return read_num_from_buffer(buf, 4);
}
uint64_t read_long_from_buffer(buffer *buf) {
    return read_num_from_buffer(buf, 8);
}

uint64_t read_number(uint8_t* ptr,uint8_t size) {
    uint64_t r = 0;
    for (int i = 0; i < size; i++) {
        r = r <<8;
        r+=ptr[i];
    }

    return r;
}

void write_number(uint8_t* ptr, uint64_t num, uint8_t size) {
    for (int i = size-1; i >-1 ; i--) {
        ptr[i] = num & 0xff;
        num = num>>8;
    }
}

void * read_dump_and_get(buffer *buf, uint32_t size) {
    void* res = buf->temp;
    buf->temp+=size;
    return res;
}
void write_dump(buffer *buf,void* o, uint32_t size) {
    mem_copy(buf->temp,(uint8_t*) o, size);
    buf->temp+=size;
}
