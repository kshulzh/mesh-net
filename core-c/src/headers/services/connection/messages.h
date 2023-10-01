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

#ifndef MESH_NET_CONNECTION_MESSAGES_H
#define MESH_NET_CONNECTION_MESSAGES_H

#include "services/message.h"
#include "model/graph.h"

typedef enum {
    REQ_ASK,
    RES_ASK,
    REQ_SET_NAME,
    RES_SET_NAME,
    REQ_GET_NAME,
    RES_GET_NAME,
    REQ_SET_ID,
    RES_SET_ID,
    REQ_GET_ID,
    RES_GET_ID,
    REQ_GET_STRUCT,
    RES_GET_STRUCT,
    REQ_UPDATE_STRUCT,
    RES_UPDATE_STRUCT
} connection_req;

typedef struct {
    basic_message bm;
    connection_req type;
} connection_message;

typedef struct {
    connection_message cm;
} connection_ask_req_message;

typedef struct {
    connection_message cm;
    codes code;
} connection_ask_res_message;

typedef struct {
    connection_message cm;
    char *name;
} connection_setname_req_message;

typedef struct {
    connection_message cm;
    codes code;
} connection_setname_res_message;

typedef struct {
    connection_message cm;
} connection_getname_req_message;

typedef struct {
    connection_message cm;
    codes code;
    char *name;
} connection_getname_res_message;

typedef struct {
    connection_message cm;
    unsigned long id;
} connection_setid_req_message;

typedef struct {
    connection_message cm;
    codes code;
} connection_setid_res_message;

typedef struct {
    connection_message cm;
} connection_getid_req_message;

typedef struct {
    connection_message cm;
    codes code;
    unsigned long id;
} connection_getid_res_message;

typedef struct {
    connection_message cm;
} connection_get_struct_req_message;

typedef struct {
    connection_message cm;
    codes code;
    graph *g;
} connection_get_struct_res_message;

typedef struct {
    connection_message cm;
    graph *g;
} connection_update_struct_req_message;

typedef struct {
    connection_message cm;
    codes code;
} connection_update_struct_res_message;

void encode_connection_ask_req_message(buffer *b, connection_ask_req_message *cm);

void encode_connection_ask_res_message(buffer *b, connection_ask_res_message *cm);


void encode_connection_setname_req_message(buffer *b, connection_setname_req_message *cm);

void encode_connection_setname_res_message(buffer *b, connection_setname_res_message *cm);

void encode_connection_getname_req_message(buffer *b, connection_getname_req_message *cm);

void encode_connection_getname_res_message(buffer *b, connection_getname_res_message *cm);


void encode_connection_setid_req_message(buffer *b, connection_setid_req_message *cm);

void encode_connection_setid_res_message(buffer *b, connection_setid_res_message *cm);

void encode_connection_getid_req_message(buffer *b, connection_getid_req_message *cm);

void encode_connection_getid_res_message(buffer *b, connection_getid_res_message *cm);


void encode_connection_get_struct_req_message(buffer *b, connection_get_struct_req_message *cm);

void encode_connection_get_struct_res_message(buffer *b, connection_get_struct_res_message *cm);

void encode_connection_update_struct_req_message(buffer *b, connection_update_struct_req_message *cm);

void encode_connection_update_struct_res_message(buffer *b, connection_update_struct_res_message *cm);

//decode

connection_ask_req_message *decode_connection_ask_req_message(buffer *b);

connection_ask_res_message *decode_connection_ask_res_message(buffer *b);


connection_setname_req_message *decode_connection_setname_req_message(buffer *b);

connection_setname_res_message *decode_connection_setname_res_message(buffer *b);

connection_getname_req_message *decode_connection_getname_req_message(buffer *b);

connection_getname_res_message *decode_connection_getname_res_message(buffer *b);


connection_setid_req_message *decode_connection_setid_req_message(buffer *b);

connection_setid_res_message *decode_connection_setid_res_message(buffer *b);

connection_getid_req_message *decode_connection_getid_req_message(buffer *b);

connection_getid_res_message *decode_connection_getid_res_message(buffer *b);


connection_get_struct_req_message *decode_connection_get_struct_req_message(buffer *b);

connection_get_struct_res_message *decode_connection_get_struct_res_message(buffer *b);

connection_update_struct_req_message *decode_connection_update_struct_req_message(buffer *b);

connection_update_struct_res_message *decode_connection_update_struct_res_message(buffer *b);

#endif //MESH_NET_CONNECTION_MESSAGES_H
