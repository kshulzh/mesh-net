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


#ifndef MESH_NET_SPREAD_MESSAGES_H
#define MESH_NET_SPREAD_MESSAGES_H

#include "services/message.h"

typedef enum {
    UDP,
    LINK,
    LINK_GRAPH
}__attribute__((packed)) spread_req;

typedef struct {
    basic_message bm;
    spread_req type: 8;
}__attribute__((packed)) spread_message;

typedef struct {
    spread_message sm;
    uint64_t src_id: 64;
    array_char *msg;
    void *inst;
}__attribute__((packed)) spread_udp_message;

typedef struct {
    spread_message sm;
    uint64_t id1;
    uint64_t id2;
}__attribute__((packed)) spread_link_message;

typedef struct {
    spread_message sm;
    uint64_t id1;
    graph *g;
}__attribute__((packed)) spread_link_graph_message;

void encode_spread_message(buffer *b, spread_message *u);

spread_message *decode_spread_message(buffer *b);

void encode_spread_udp_message(buffer *b, spread_udp_message *u);

spread_udp_message *decode_spread_udp_message(buffer *b);

void encode_spread_link_message(buffer *b, spread_link_message *u);

spread_link_message *decode_spread_link_message(buffer *b);

void encode_spread_link_graph_message(buffer *b, spread_link_graph_message *u);

spread_link_graph_message *decode_spread_link_graph_message(buffer *b);

#endif //MESH_NET_SPREAD_MESSAGES_H
