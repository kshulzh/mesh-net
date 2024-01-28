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
#include "services/spread/functions.h"

message_handler *connection_message_handlers() {
    static message_handler connection_message_handlers[14];
    return connection_message_handlers;
}


void connection_handle_ask_req(message *m) {
//    buffer b;
//    buffer_init(&b, m->bm.size, m->bytes);
    // connection_ask_req_message *c = decode_connection_ask_req_message(&b);
    LOG_INFO("req")
    connection_ask_res(m, OK);
}

void connection_handle_ask_res(message *m) {
    //todo
    LOG_INFO("res")
}

void connection_handle_get_struct_req(message *m) {
    connection_get_struct_res(m, ((instance *) m->c->r->inst)->g, OK);
}

void connection_handle_get_struct_res(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    connection_get_struct_res_message *gs = decode_connection_get_struct_res_message(&b);
    m->c->d = *((device *) gs->g->this_node.element);
    instance *inst = ((instance *) m->c->r->inst);
    graph_add_graph(inst->g, 0, gs->g);
    //todo
    gs->g->encode = inst->g->encode;
    spread_link_graph(inst, gs->g);
}

void connection_handle_get_property_req(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    connection_get_property_req_message *cm = decode_connection_get_property_req_message(&b);
    instance *inst = ((instance *) m->c->r->inst);
    if (cm->property == PROPERTY_ID) {
        dynamic value;
        value.type = INT64;
        value.value.uint64 = inst->this_device.id;
        connection_get_property_res(m->c, cm->property, value, OK);
    } else {
        dynamic value;
        connection_get_property_res(m->c, cm->property, value, ERROR);
    }
}

void connection_handle_get_property_res(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    connection_get_property_res_message *cm = decode_connection_get_property_res_message(&b);
    if (cm->property == PROPERTY_ID) {
        m->c->d.id = cm->value.value.uint64;

    }

}

void connection_handle(message *m) {
    connection_message *cm = ((connection_message *) m->bytes);
    connection_message_handlers()[cm->type](m);
}

void connection_setup() {
    message_handlers()[CONNECTION] = connection_handle;

    connection_message_handlers()[REQ_ASK] = connection_handle_ask_req;
    connection_message_handlers()[RES_ASK] = connection_handle_ask_res;

    connection_message_handlers()[REQ_GET_STRUCT] = connection_handle_get_struct_req;
    connection_message_handlers()[RES_GET_STRUCT] = connection_handle_get_struct_res;

    connection_message_handlers()[REQ_GET_PROPERTY] = connection_handle_get_property_req;
    connection_message_handlers()[RES_GET_PROPERTY] = connection_handle_get_property_res;
}
