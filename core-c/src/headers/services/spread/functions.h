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

#ifndef MESH_NET_SPREAD_FUNCTIONS_H
#define MESH_NET_SPREAD_FUNCTIONS_H

#include "model/instance.h"
#include "services/message.h"

void spread_udp(instance *c, uint8_t *msg, uint32_t size);

void spread_res(message *m);

void spread_all(list *connections, uint8_t *data, uint32_t size_data, uint64_t *exclude, uint32_t size_exclude);

void spread_link(instance *c, uint64_t id2);

void spread_link_graph(instance *c, graph *g);

void spread_unlink(instance *c, uint64_t id1, uint64_t id2);

#endif //MESH_NET_ROUTE_FUNCTIONS_H
