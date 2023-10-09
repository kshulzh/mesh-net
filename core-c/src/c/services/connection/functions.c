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
    c->write_array(c, (char *) (&req), sizeof(connection_ask_req_message));
}

void connection_setname(connection *c, char *name, unsigned int size) {

}

void connection_getname(connection *c) {

}

void connection_setid(connection *c, long id) {

}

void connection_getid(connection *c) {

}

void connection_get_struct(connection *c) {
    buffer b;
    char* bytes[100];
    buffer_init(&b,100,bytes);
    connection_ask_req_message req;
    req.cm.bm.type = CONNECTION;
    req.cm.type = REQ_GET_STRUCT;
    encode_connection_get_struct_req_message(&b,&req);
    c->write_array(c, b.start, (b.temp) - (b.start));
}

void connection_update_struct(connection *c, graph *g) {

}

void connection_ask_res(message *m, codes code) {
    buffer b;
    char* bytes[100];
    buffer_init(&b,100,bytes);
    connection_ask_res_message res;
    res.cm.bm = m->bm;
    res.cm.type = RES_ASK;
    res.code = code;
    encode_connection_ask_req_message(&b,&res);
    res.cm.bm.size = buffer_message_set_size(&b);

    m->c->write_array(m->c, b.start, b.temp-b.start);
}

void connection_setname_res(message *m, codes code) {

}

void connection_getname_res(message *m, char *name, unsigned int size, codes code) {

}

void connection_setid_res(message *m, codes code) {

}

void connection_getid_res(message *m, long id, codes code) {

}

void connection_get_struct_res(message *m, graph *g, codes code) {
    connection_get_struct_res_message res;
    connection_init_message((&(res.cm)), RES_GET_STRUCT);
    res.g = g;
    res.code = code;
    buffer *b = list_find_first(&(((instance *) m->c->r->inst)->buffers), buffer_is_free());
    b->is_locked = 1;
    buffer_reset(b);
    encode_connection_get_struct_res_message(b, &res);
    buffer_message_set_size(b);
    m->c->write_array(m->c, b->start, (b->temp) - (b->start));
    buffer_reset(b);
    b->is_locked = 0;
}

void connection_update_struct_res(message *m, codes code) {

}