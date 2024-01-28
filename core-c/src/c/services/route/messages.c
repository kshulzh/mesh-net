
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
    write_dump(b, rm, sizeof(route_message));
}

route_message *decode_route_message(buffer *b) {
    return read_dump_and_get(b, sizeof(route_message));
}

void encode_route_udp_message(buffer *b, route_udp_message *u) {
    write_dump(b, u, sizeof(route_udp_message));
    encode_list(b, u->way, encode_device_id);
    encode_char_array(b, u->msg);
    u->rm.bm.size = buffer_message_set_size(b);
}

route_udp_message *decode_route_udp_message(buffer *b) {
    route_udp_message *rum = read_dump_and_get(b, sizeof(route_udp_message));
    rum->way = decode_list(b, decode_uint64);
    rum->msg = decode_char_array(b);
    return rum;
}
