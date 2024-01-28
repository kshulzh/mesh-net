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


#ifndef MESH_NET_ROUTE_HANDLERS_H
#define MESH_NET_ROUTE_HANDLERS_H

#include "services/message.h"
#include "services/handlers.h"
#include "messages.h"

message_handler *route_message_handlers();

typedef void (*udp_handler)(route_udp_message *);

udp_handler *udp_handler1();

void route_handle_udp(message *m);

void route_handle(message *m);

void route_setup();

#endif //MESH_NET_HANDLERS_H
