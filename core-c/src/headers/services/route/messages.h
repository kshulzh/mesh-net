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


#ifndef MESH_NET_ROUTE_MESSAGES_H
#define MESH_NET_ROUTE_MESSAGES_H

#include "services/message.h"

typedef enum {
    UDP
}__attribute__((packed))  route_req;

typedef struct {
    basic_message bm;
    route_req type;
}__attribute__((packed))  route_message;

typedef struct {
    route_message rm;
    int index;
    list *way;
    array_char *msg;
    void *inst;
}__attribute__((packed))  route_udp_message;

void encode_route_message(buffer *b, route_message *u);

route_message *decode_route_message(buffer *b);

void encode_route_udp_message(buffer *b, route_udp_message *u);

route_udp_message *decode_route_udp_message(buffer *b);


#endif //MESH_NET_ROUTE_MESSAGES_H
