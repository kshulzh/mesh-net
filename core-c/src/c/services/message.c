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

#include "services/message.h"
#include "utils/new.h"

message *message_of_buffer(buffer *b) {
    message *m = New(message);
    m->bytes = b->start;
    buffer_reset(b);
    m->bm = *decode_basic_message(b);
    buffer_reset(b);
    return m;
}

void encode_basic_message(buffer *b, basic_message *bm) {
    write_short_to_buffer(b,bm->size);
    write_char_to_buffer(b,bm->type);
    write_long_to_buffer(b, bm->message_id);
}

basic_message* decode_basic_message(buffer *b) {
    static basic_message bm;
    bm.size = read_short_from_buffer(b);
    bm.type = read_char_from_buffer(b);
    bm.message_id = read_long_from_buffer(b);
    return &bm;
}
