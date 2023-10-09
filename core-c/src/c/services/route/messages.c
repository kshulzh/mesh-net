
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

#include "services/route/messages.h"
#include "io/writers/writers.h"
#include "services/utils.h"
#include "io/readers/readers.h"

void encode_route_message(buffer *b, route_message *rm) {
    encode_basic_message(b,&(rm->bm));
    write_char_to_buffer(b, rm->type);
}

route_message *decode_route_message(buffer *b) {
    static route_message rm;
    rm.bm = *decode_basic_message(b);
    rm.type = read_char_from_buffer(b);
    return &rm;
}

void encode_route_udp_message(buffer *b, route_udp_message *u) {
    encode_route_message(b,&(u->rm));
    write_int_to_buffer(b,u->index);
    encode_list(b, u->way, encode_device_id);
    encode_char_array(b, u->msg);
    u->rm.bm.size = buffer_message_set_size(b);
}

route_udp_message *decode_route_udp_message(buffer *b) {
    static route_udp_message rum;
    rum.rm = *decode_route_message(b);
    rum.index = read_int_from_buffer(b);
    rum.way = decode_list(b, decode_uint64);
    rum.msg = decode_char_array(b);
    return &rum;
}
