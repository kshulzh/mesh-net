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

#include "services/connection/functions.h"
#include "services/connection/messages.h"
#include "services/utils.h"
#include "log/connection_logger.h"

void connection_ask(connection *c) {
    connection_ask_req_message req;
    req.cm.bm.size = sizeof(req);
    req.cm.bm.type = CONNECTION;
    req.cm.type = REQ_ASK;
    CONNECTION_LOG_DEBUG(c, "Sending ask request", 0);
    c->write_array(c, (uint8_t *) (&req), sizeof(connection_ask_req_message));
}

void connection_get_struct(connection *c) {
    connection_ask_req_message req;
    req.cm.bm.size = sizeof(connection_ask_req_message);
    req.cm.bm.type = CONNECTION;
    req.cm.type = REQ_GET_STRUCT;
    CONNECTION_LOG_DEBUG(c, "Sending get struct request", 0);
    c->write_array(c, (uint8_t *) &req, sizeof(connection_ask_req_message));
}

void connection_ask_res(message *m, codes code) {
    connection_ask_res_message res;
    res.cm.bm = m->bm;
    res.cm.type = RES_ASK;
    res.code = code;
    res.cm.bm.size = sizeof(connection_ask_res_message);

    CONNECTION_LOG_DEBUG(m->c, "Sending ask response", 0);
    m->c->write_array(m->c, (uint8_t *) &res, sizeof(connection_ask_res_message));
}

void connection_get_property(connection *c, uint8_t property) {
    connection_get_property_req_message req;
    req.cm.bm.size = sizeof(connection_get_property_req_message);
    req.cm.bm.type = CONNECTION;
    req.cm.type = REQ_GET_PROPERTY;
    req.property = property;

    CONNECTION_LOG_DEBUG(c, "Sending get property request with id:%d", property);
    c->write_array(c, (uint8_t *) &req, sizeof(connection_get_property_req_message));
}

void connection_get_property_res(connection *c, uint8_t property, dynamic value, codes code) {
    connection_get_property_res_message res;
    res.cm.bm.size = sizeof(connection_get_property_res_message);
    res.cm.bm.type = CONNECTION;
    res.cm.type = RES_GET_PROPERTY;
    res.property = property;
    res.value = value;
    res.code = code;

    CONNECTION_LOG_DEBUG(c, "Sending get property response with id:%d", property);
    c->write_array(c, (uint8_t *) &res, sizeof(connection_get_property_res_message));
}

void connection_get_struct_res(message *m, graph *g, codes code) {
    connection_get_struct_res_message res;
    res.cm.bm.type = CONNECTION;
    res.cm.type = RES_GET_STRUCT;
    res.g = g;
    res.code = code;
    buffer *b = list_find_first(&(((instance *) m->c->r->inst)->buffers), buffer_is_free());
    if (b) {
        b->is_locked = 1;
        buffer_reset(b);
        connection_get_struct_res_message *ptr = New(connection_get_struct_res_message);
        *ptr = res;
        encode_connection_get_struct_res_message(b, ptr);
        buffer_message_set_size(b);
        CONNECTION_LOG_DEBUG(m->c, "Sending get struct response", 0);
        m->c->write_array(m->c, b->start, (b->temp) - (b->start));
        buffer_reset(b);
        b->is_locked = 0;
    } else {
        //todo
    }
}