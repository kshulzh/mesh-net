//
// Created by kirill on 28.09.23.
//

#ifndef MESH_NET_ROUTE_MESSAGES_H
#define MESH_NET_ROUTE_MESSAGES_H

#include "services/message.h"
typedef enum {
    UDP
} route_req;

typedef struct {
    basic_message bm;
    route_req type;
} route_message;

typedef struct {
    basic_message rm;
    list *way;
    int index;
    array_char *msg;
    void * inst;
} route_udp_message;

void encode_route_message(buffer *b, route_message *u);

route_message* decode_route_message(buffer *b);

void encode_route_udp_message(buffer *b, route_udp_message *u);

route_udp_message* decode_route_udp_message(buffer *b);


#endif //MESH_NET_ROUTE_MESSAGES_H
