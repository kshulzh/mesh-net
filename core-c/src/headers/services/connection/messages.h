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

#ifndef MESH_NET_CONNECTION_MESSAGES_H
#define MESH_NET_CONNECTION_MESSAGES_H

#include "services/message.h"
#include "model/graph.h"
#include "utils/dynamic.h"

#define PROPERTY_ID 1
typedef enum {
    REQ_ASK,
    RES_ASK,
    REQ_GET_STRUCT,
    RES_GET_STRUCT,
    REQ_GET_PROPERTY,
    RES_GET_PROPERTY
} __attribute__((packed)) connection_req;

typedef struct {
    basic_message bm;
    connection_req type;
} __attribute__((packed)) connection_message;

typedef struct {
    connection_message cm;
} __attribute__((packed)) connection_ask_req_message;

typedef struct {
    connection_message cm;
    codes code;
} __attribute__((packed)) connection_ask_res_message;

typedef struct {
    connection_message cm;
} __attribute__((packed)) connection_get_struct_req_message;

typedef struct {
    connection_message cm;
    codes code;
    graph *g;
} __attribute__((packed)) connection_get_struct_res_message;

typedef struct {
    connection_message cm;
    uint8_t property;
} __attribute__((packed)) connection_get_property_req_message;

typedef struct {
    connection_message cm;
    uint8_t property;
    dynamic value;
    codes code;
} __attribute__((packed)) connection_get_property_res_message;

typedef struct {
    connection_message cm;
    graph *g;
} connection_update_struct_req_message;

typedef struct {
    connection_message cm;
    codes code;
} connection_update_struct_res_message;

void encode_connection_message(buffer *b, connection_message *cm);


void encode_connection_ask_req_message(buffer *b, connection_ask_req_message *cm);

void encode_connection_ask_res_message(buffer *b, connection_ask_res_message *cm);


void encode_connection_get_struct_req_message(buffer *b, connection_get_struct_req_message *cm);

void encode_connection_get_struct_res_message(buffer *b, connection_get_struct_res_message *cm);

void encode_connection_get_property_req_message(buffer *b, connection_get_property_req_message *cm);

void encode_connection_get_property_res_message(buffer *b, connection_get_property_res_message *cm);
//decode

connection_message *decode_connection_message(buffer *b);


connection_ask_req_message *decode_connection_ask_req_message(buffer *b);

connection_ask_res_message *decode_connection_ask_res_message(buffer *b);


connection_get_struct_req_message *decode_connection_get_struct_req_message(buffer *b);

connection_get_struct_res_message *decode_connection_get_struct_res_message(buffer *b);

connection_get_property_req_message *decode_connection_get_property_req_message(buffer *b);

connection_get_property_res_message *decode_connection_get_property_res_message(buffer *b);

#endif //MESH_NET_CONNECTION_MESSAGES_H
