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

#include "services/connection/messages.h"

void encode_connection_ask_req_message(buffer *b, connection_ask_req_message *cm) {
    write_to_buffer(b,cm, sizeof(connection_ask_req_message));
}

void encode_connection_ask_res_message(buffer *b, connection_ask_res_message *cm) {
    write_to_buffer(b,cm, sizeof(connection_ask_res_message));
}


void encode_connection_setname_req_message(buffer *b, connection_setname_req_message *cm) {

}

void encode_connection_setname_res_message(buffer *b, connection_setname_res_message *cm) {

}

void encode_connection_getname_req_message(buffer *b, connection_getname_req_message *cm) {

}

void encode_connection_getname_res_message(buffer *b, connection_getname_res_message *cm) {

}


void encode_connection_setid_req_message(buffer *b, connection_setid_req_message *cm) {

}

void encode_connection_setid_res_message(buffer *b, connection_setid_res_message *cm) {

}

void encode_connection_getid_req_message(buffer *b, connection_getid_req_message *cm) {

}

void encode_connection_getid_res_message(buffer *b, connection_getid_res_message *cm) {

}


void encode_connection_get_struct_req_message(buffer *b, connection_get_struct_req_message *cm) {
    write_to_buffer(b,cm, sizeof(connection_get_struct_req_message));
}

void encode_connection_get_struct_res_message(buffer *b, connection_get_struct_res_message *cm) {
    write_to_buffer(b,cm, sizeof(connection_get_struct_res_message));
    encode_graph(b,cm->g);
}

void encode_connection_update_struct_req_message(buffer *b, connection_update_struct_req_message *cm) {

}

void encode_connection_update_struct_res_message(buffer *b, connection_update_struct_res_message *cm) {

}

//decode

connection_ask_req_message *decode_connection_ask_req_message(buffer *b) {
    return (connection_ask_req_message *) read_from_buffer(b, sizeof(connection_ask_req_message));
}

connection_ask_res_message *decode_connection_ask_res_message(buffer *b) {
    return (connection_ask_res_message *) read_from_buffer(b, sizeof(connection_ask_res_message));
}


connection_setname_req_message *decode_connection_setname_req_message(buffer *b) {

}

connection_setname_res_message *decode_connection_setname_res_message(buffer *b) {

}

connection_getname_req_message *decode_connection_getname_req_message(buffer *b) {

}

connection_getname_res_message *decode_connection_getname_res_message(buffer *b) {

}


connection_setid_req_message *decode_connection_setid_req_message(buffer *b) {

}

connection_setid_res_message *decode_connection_setid_res_message(buffer *b) {

}

connection_getid_req_message *decode_connection_getid_req_message(buffer *b) {

}

connection_getid_res_message *decode_connection_getid_res_message(buffer *b) {

}


connection_get_struct_req_message *decode_connection_get_struct_req_message(buffer *b) {
    return (connection_get_struct_req_message *) read_from_buffer(b, sizeof(connection_get_struct_req_message));
}

connection_get_struct_res_message *decode_connection_get_struct_res_message(buffer *b) {
    connection_get_struct_res_message *cm = (connection_get_struct_res_message *) read_from_buffer(b, sizeof(connection_get_struct_res_message));
    cm->g = decode_graph(b, decode_device, device_clone);
    return cm;
}

connection_update_struct_req_message *decode_connection_update_struct_req_message(buffer *b) {

}

connection_update_struct_res_message *decode_connection_update_struct_res_message(buffer *b) {

}
