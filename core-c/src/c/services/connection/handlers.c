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

#include "services/connection/handlers.h"
#include "services/connection/functions.h"
#include "log/logger.h"
#include "services/utils.h"

message_handler *connection_message_handlers() {
    static message_handler connection_message_handlers[14];
    return connection_message_handlers;
}


void connection_handle_ask_req(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    connection_ask_req_message *c = decode_connection_ask_req_message(&b);
    LOG_INFO("req")
    connection_ask_res(m, OK);
}

void connection_handle_ask_res(message *m) {
    //todo
    LOG_INFO("res")
}

void connection_handle_get_struct_req(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    connection_get_struct_req_message *gs = decode_connection_get_struct_req_message(&b);
    connection_get_struct_res(m, ((instance *) m->c->r->inst)->g, OK);
}

void connection_handle_get_struct_res(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    connection_get_struct_res_message *gs = decode_connection_get_struct_res_message(&b);
    m->c->d = *((device*)gs->g->this_node.element);
    instance * inst = ((instance *) m->c->r->inst);
    graph_add_graph(inst->g, 0, gs->g);
    //todo
}

void connection_handle(message *m) {
    buffer  b1;
    buffer_init(&b1,100,m->bytes);
    connection_message cm = *decode_connection_message(&b1);
    connection_message_handlers()[cm.type](m);
}

void connection_setup() {
    message_handlers()[CONNECTION] = connection_handle;
    connection_message_handlers()[REQ_ASK] = connection_handle_ask_req;
    connection_message_handlers()[RES_ASK] = connection_handle_ask_res;

    connection_message_handlers()[REQ_GET_STRUCT] = connection_handle_get_struct_req;
    connection_message_handlers()[RES_GET_STRUCT] = connection_handle_get_struct_res;
}
