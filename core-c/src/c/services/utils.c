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

#include "services/utils.h"

short buffer_message_set_size(buffer *b) {
    return *((short *) b->start) = (short) ((b->temp) - (b->start));
}

void free_uint32(void *v) {
    mem_free((unsigned int *) v);
}

void *decode_uint32(buffer *b) {
    return (void*) read_int_from_buffer(b);
}

void encode_uint32(buffer *b, unsigned int i) {
    write_int_to_buffer(b,i);
}

void encode_link(buffer *b, void *l) {
    write_to_buffer(b, &l, sizeof(void *));
}

void *decode_link(buffer *b) {
    return read_from_buffer(b, sizeof(void *));
}

void *decode_uint64(buffer *b) {
    return (unsigned long *) read_from_buffer(b, 8);
}
