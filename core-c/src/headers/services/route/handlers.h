//
// Created by kirill on 28.09.23.
//

#ifndef MESH_NET_ROUTE_HANDLERS_H
#define MESH_NET_ROUTE_HANDLERS_H
#include "services/message.h"
#include "services/handlers.h"
#include "messages.h"

message_handler* route_message_handlers();
typedef void (*udp_handler) (route_udp_message *);

udp_handler* udp_handler1();

void route_handle_udp(message *m);

void route_handle(message*m);

void route_setup();

#endif //MESH_NET_HANDLERS_H
