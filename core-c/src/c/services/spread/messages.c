/*
 * Copyright (c) 2024. Kirill Shulzhenko
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

#include "services/spread/messages.h"
#include "io/writers/writers.h"
#include "io/readers/readers.h"
#include "services/utils.h"

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
    write_dump(b, u, sizeof(spread_message));
}


spread_message *decode_spread_message(buffer *b) {
    return read_dump_and_get(b, sizeof(spread_message));
}

void encode_spread_udp_message(buffer *b, spread_udp_message *u) {
    write_dump(b, u, sizeof(spread_udp_message));
    encode_char_array(b, u->msg);
    u->sm.bm.size = buffer_message_set_size(b);
}

spread_udp_message *decode_spread_udp_message(buffer *b) {
    spread_udp_message *sm = read_dump_and_get(b, sizeof(spread_udp_message));
    sm->msg = decode_char_array(b);

    return sm;
}

void encode_spread_link_message(buffer *b, spread_link_message *u) {
    write_dump(b, u, sizeof(spread_link_message));
}

spread_link_message *decode_spread_link_message(buffer *b) {
    return read_dump_and_get(b, sizeof(spread_link_message));
}

void encode_spread_link_graph_message(buffer *b, spread_link_graph_message *u) {
    write_dump(b, u, sizeof(spread_link_graph_message));
    encode_graph(b, u->g);
}

spread_link_graph_message *decode_spread_link_graph_message(buffer *b) {
    spread_link_graph_message *slgm = read_dump_and_get(b, sizeof(spread_link_message));
    slgm->g = decode_graph(b, decode_device, device_clone);

    return slgm;
}