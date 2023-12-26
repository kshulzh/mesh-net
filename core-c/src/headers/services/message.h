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

#ifndef MESH_NET_MESSAGE_H
#define MESH_NET_MESSAGE_H

#include "io/connection/connection.h"
#include "io/buffer.h"

typedef
enum {
    CONNECTION,
    SPREAD,
    ROUTE
} __attribute__((packed)) message_type;

typedef enum {
    OK,
    ERROR
} __attribute__((packed)) codes;

//#pragma pack(1)
typedef
struct {
    uint16_t size : 16;
    uint64_t message_id : 64;
    message_type type : 8;
} __attribute__((packed)) basic_message;
//const uint32_t basic_message_size = sizeof(basic_message);

typedef struct {
    basic_message bm;
    uint8_t *bytes;
    connection *c;
} message;

message *message_of_buffer(buffer *b);

void encode_basic_message(buffer *b, basic_message *bm);

basic_message* decode_basic_message(buffer *b);

#endif //MESH_NET_MESSAGE_H
