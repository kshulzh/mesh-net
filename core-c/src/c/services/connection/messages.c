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
#include "services/utils.h"

void encode_connection_message(buffer *b, connection_message *cm) {
    encode_basic_message(b,&(cm->bm));
    write_char_to_buffer(b,cm->type);
}
void encode_connection_ask_req_message(buffer *b, connection_ask_req_message *cm) {
    encode_connection_message(b,&(cm->cm));
    buffer_message_set_size(b);
}

void encode_connection_ask_res_message(buffer *b, connection_ask_res_message *cm) {
    encode_connection_message(b,&(cm->cm));
    write_char_to_buffer(b,cm->code);
    buffer_message_set_size(b);
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
    encode_connection_message(b,&(cm->cm));
    buffer_message_set_size(b);
}

void encode_connection_get_struct_res_message(buffer *b, connection_get_struct_res_message *cm) {
    encode_connection_message(b,&(cm->cm));
    write_char_to_buffer(b,cm->code);
    encode_graph(b, cm->g);
    buffer_message_set_size(b);
}

void encode_connection_update_struct_req_message(buffer *b, connection_update_struct_req_message *cm) {

}

void encode_connection_update_struct_res_message(buffer *b, connection_update_struct_res_message *cm) {

}

//decode
connection_message * decode_connection_message(buffer *b) {
    connection_message cm;
    cm.bm = *decode_basic_message(b);

    cm.type = read_char_from_buffer(b);
    return &cm;
}

connection_ask_req_message *decode_connection_ask_req_message(buffer *b) {
    connection_ask_req_message cm;
    cm.cm = *decode_connection_message(b);
    return &cm;
}

connection_ask_res_message *decode_connection_ask_res_message(buffer *b) {
    connection_ask_res_message cm;
    cm.cm = *decode_connection_message(b);
    cm.code = read_char_from_buffer(b);
    return &cm;
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
    connection_get_struct_req_message cm;
    cm.cm = *decode_connection_message(b);
    return &cm;
}

connection_get_struct_res_message *decode_connection_get_struct_res_message(buffer *b) {
    connection_get_struct_res_message cm;
    cm.cm = *decode_connection_message(b);
    cm.code = read_char_from_buffer(b);
    cm.g = decode_graph(b, decode_device, device_clone);
    return &cm;
}

connection_update_struct_req_message *decode_connection_update_struct_req_message(buffer *b) {

}

connection_update_struct_res_message *decode_connection_update_struct_res_message(buffer *b) {

}
