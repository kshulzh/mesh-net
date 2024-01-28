
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
    short size = ((b->temp) - (b->start));
    mem_copy(b->start, &size, 2);

    return size;
}

void free_uint32(void *v) {
    mem_free((unsigned int *) v);
}

void *decode_uint32(buffer *b) {
    return read_dump_and_get(b, sizeof(uint32_t));
}

void *decode_link(buffer *b) {
    return read_from_buffer(b, sizeof(void *));
}

void *decode_uint64(buffer *b) {
    return read_dump_and_get(b, sizeof(uint64_t));
}
