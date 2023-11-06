#include "services/spread/messages.h"
#include "io/writers/writers.h"
#include "io/readers/readers.h"

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

void encode_spread_message(buffer *b, spread_message *u) {
    encode_basic_message(b,&u->bm);
    write_char_to_buffer(b,u->type);
}


spread_message *decode_spread_message(buffer *b) {
    static spread_message sm;
    sm.bm = *decode_basic_message(b);
    sm.type = read_char_from_buffer(b);

    return &sm;
}

void encode_spread_udp_message(buffer *b, spread_udp_message *u) {
    encode_spread_message(b,&u->sm);
    write_long_to_buffer(b,u->src_id);
    encode_char_array(b, u->msg);
}

spread_udp_message *decode_spread_udp_message(buffer *b) {
    static spread_udp_message sm;

    sm.sm = *decode_spread_message(b);
    sm.src_id = read_long_from_buffer(b);
    sm.msg = decode_char_array(b);

    return &sm;
}