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


#ifndef MESH_NET_SPREAD_ROUTE_HANDLERS_H
#define MESH_NET_SPREAD_ROUTE_HANDLERS_H

#include "services/message.h"
#include "services/handlers.h"
#include "messages.h"

message_handler *spread_message_handlers();

typedef void (*spread_udp_handler)(spread_udp_message *);

spread_udp_handler *spread_udp_handler1();

void spread_handle_udp(message *m);

void spread_handle(message *m);

void spread_setup();

#endif //MESH_SPREAD_NET_HANDLERS_H
