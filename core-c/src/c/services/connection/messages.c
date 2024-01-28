/*
 * Copyright (c) 2023-2024. Kirill Shulzhenko
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

#include "services/connection/messages.h"
#include "services/utils.h"

void encode_connection_message(buffer *b, connection_message *cm) {
    write_dump(b, cm, sizeof(connection_message));
}

void encode_connection_ask_req_message(buffer *b, connection_ask_req_message *cm) {
    write_dump(b, cm, sizeof(connection_ask_req_message));
    buffer_message_set_size(b);
}

void encode_connection_ask_res_message(buffer *b, connection_ask_res_message *cm) {
    write_dump(b, cm, sizeof(connection_ask_res_message));
    buffer_message_set_size(b);
}

void encode_connection_get_struct_req_message(buffer *b, connection_get_struct_req_message *cm) {
    write_dump(b, cm, sizeof(connection_get_struct_req_message));
    cm->cm.bm.size = buffer_message_set_size(b);
}

void encode_connection_get_struct_res_message(buffer *b, connection_get_struct_res_message *cm) {
    write_dump(b, cm, sizeof(connection_get_struct_res_message));
    encode_graph(b, cm->g);
    cm->cm.bm.size = buffer_message_set_size(b);
}

void encode_connection_get_property_req_message(buffer *b, connection_get_property_req_message *cm) {
    write_dump(b, cm, sizeof(encode_connection_get_property_req_message));
    cm->cm.bm.size = buffer_message_set_size(b);
}

void encode_connection_get_property_res_message(buffer *b, connection_get_property_res_message *cm) {
    write_dump(b, cm, sizeof(encode_connection_get_property_req_message));
    cm->cm.bm.size = buffer_message_set_size(b);
}

//decode
connection_message *decode_connection_message(buffer *b) {
    return read_dump_and_get(b, sizeof(connection_message));
}

connection_ask_req_message *decode_connection_ask_req_message(buffer *b) {
    return read_dump_and_get(b, sizeof(connection_ask_req_message));
}

connection_ask_res_message *decode_connection_ask_res_message(buffer *b) {
    return read_dump_and_get(b, sizeof(connection_ask_res_message));
}

connection_get_struct_req_message *decode_connection_get_struct_req_message(buffer *b) {
    return read_dump_and_get(b, sizeof(connection_get_struct_req_message));
}

connection_get_struct_res_message *decode_connection_get_struct_res_message(buffer *b) {
    connection_get_struct_res_message *cm = read_dump_and_get(b, sizeof(connection_get_struct_res_message));
    cm->g = decode_graph(b, decode_device, device_clone);
    return cm;
}

connection_get_property_req_message *decode_connection_get_property_req_message(buffer *b) {
    //todo
    return read_dump_and_get(b, sizeof(connection_get_property_req_message));
}

connection_get_property_res_message *decode_connection_get_property_res_message(buffer *b) {
    //todo
    return read_dump_and_get(b, sizeof(connection_get_property_res_message));
}
