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

#include "services/connection/functions.h"
#include "services/connection/messages.h"
#include "services/utils.h"

static void connection_init_message(connection_message *cm, connection_req type) {
    cm->type = type;
    cm->bm.type = CONNECTION;
}

void connection_ask(connection *c) {
    connection_ask_req_message req;
    connection_init_message((&(req.cm)), REQ_ASK);
    req.cm.bm.size = sizeof(req);
    c->write_array(c, (uint8_t *) (&req), sizeof(connection_ask_req_message));
}

void connection_get_struct(connection *c) {
    connection_ask_req_message req;
    req.cm.bm.type = CONNECTION;
    req.cm.type = REQ_GET_STRUCT;
    req.cm.bm.size = sizeof(connection_ask_req_message);

    c->write_array(c, (uint8_t *)  &req, sizeof(connection_ask_req_message));
}

void connection_update_struct(connection *c, graph *g) {

}

void connection_ask_res(message *m, codes code) {
    connection_ask_res_message res;
    res.cm.bm = m->bm;
    res.cm.type = RES_ASK;
    res.code = code;
    res.cm.bm.size = sizeof(connection_ask_res_message);

    m->c->write_array(m->c, (uint8_t *)  &res, sizeof(connection_ask_res_message));
}

void connection_get_property(connection* c, uint8_t property) {
    connection_get_property_req_message req;
    req.cm.bm.size = sizeof(connection_get_property_req_message);
    req.cm.bm.type = CONNECTION;
    req.cm.type = REQ_GET_PROPERTY;
    req.property = property;

    c->write_array(c, (uint8_t *)  &req, sizeof(connection_get_property_req_message));
}

void connection_get_property_res(connection* c, uint8_t property, dynamic value, codes code) {
    connection_get_property_res_message res;
    res.cm.bm.size = sizeof(connection_get_property_res_message);
    res.cm.bm.type = CONNECTION;
    res.cm.type = RES_GET_PROPERTY;
    res.property = property;
    res.value = value;
    res.code = code;

    c->write_array(c, (uint8_t *)  &res, sizeof(connection_get_property_res_message));
}

void connection_get_struct_res(message *m, graph *g, codes code) {
    connection_get_struct_res_message res;
    connection_init_message((&(res.cm)), RES_GET_STRUCT);
    res.g = g;
    res.code = code;
    buffer *b = list_find_first(&(((instance *) m->c->r->inst)->buffers), buffer_is_free());
    if(b) {
        b->is_locked = 1;
        buffer_reset(b);
        connection_get_struct_res_message *ptr = New(connection_get_struct_res_message);
        *ptr = res;
        encode_connection_get_struct_res_message(b, ptr);
        buffer_message_set_size(b);
        m->c->write_array(m->c, b->start, (b->temp) - (b->start));
        buffer_reset(b);
        b->is_locked = 0;
    } else {
        //todo
    }
}

void connection_update_struct_res(message *m, codes code) {

}