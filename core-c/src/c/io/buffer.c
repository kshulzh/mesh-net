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
void buffer_init(buffer *buf, uint32_t size, char *arr) {
    buf->size = size;
    buf->start = arr;
    buf->end = arr + size;
    buf->temp = arr;
    buf->is_locked = 0;
}

extern
char *mem_copy(char *dest, const char *src, uint32_t size) {
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

buffer *new_buffer(char *data, unsigned int size) {
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

char * write_num_to_buffer(buffer *buf,long long d, int size) {
    char* res = buf->temp;
    for (int i = size-1; i >-1 ; --i) {
        buf->temp[i] = d & 0xff;
        d = d>>8;
    }
    buf->temp+=size;

    return res;
}


char *write_char_to_buffer(buffer *buf, char d) {
    return write_num_to_buffer(buf,d,1);
}

char *write_short_to_buffer(buffer *buf, short d) {
    return write_num_to_buffer(buf,d,2);
}
char *write_int_to_buffer(buffer *buf, int d) {
    return write_num_to_buffer(buf,d,4);
}
char *write_long_to_buffer(buffer *buf, long d) {
    return write_num_to_buffer(buf,d,8);
}
long read_num_from_buffer(buffer *buf, int size) {
    long r = 0;
    for (int i = 0; i < size; ++i) {
        r = r <<8;
        r+=buf->temp[0];
        buf->temp++;
    }

    return r;
}
char read_char_from_buffer(buffer *buf) {
    return read_num_from_buffer(buf, 1);
}

short read_short_from_buffer(buffer *buf) {
    return read_num_from_buffer(buf, 2);
}
int read_int_from_buffer(buffer *buf) {
    return read_num_from_buffer(buf, 4);
}
long read_long_from_buffer(buffer *buf) {
    return read_num_from_buffer(buf, 8);
}
