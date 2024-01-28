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

#ifndef MESH_NET_CONNECTION_FUNCTIONS_H
#define MESH_NET_CONNECTION_FUNCTIONS_H

#include "io/connection/connection.h"
#include "model/graph.h"
#include "services/message.h"
#include "utils/dynamic.h"

void connection_ask(connection *c);

void connection_get_struct(connection *c);

void connection_ask_res(message *m, codes code);

void connection_get_struct_res(message *m, graph *g, codes code);

void connection_get_property(connection *c, uint8_t property);

void connection_get_property_res(connection *c, uint8_t property, dynamic value, codes code);

#endif //MESH_NET_CONNECTION_FUNCTIONS_H
