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

#include "services/message.h"
#include "services/handlers.h"

#ifndef MESH_NET_CONNECTION_HANDLER_H
#define MESH_NET_CONNECTION_HANDLER_H
message_handler* connection_message_handlers();

void connection_handle_ask_req(message*m);

void connection_handle_ask_res(message*m);

void connection_handle_get_struct_req(message*m);

void connection_handle_get_struct_res(message*m);

void connection_handle(message*m);

void connection_setup();
#endif //MESH_NET_CONNECTION_HANDLER_H
