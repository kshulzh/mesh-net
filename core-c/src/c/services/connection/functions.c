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

static void connection_init_message(connection_message *cm,connection_req type) {
    cm->type = type;
    cm->bm.type = CONNECTION;
}
void connection_ask(connection *c) {
    connection_ask_req_message req;
    connection_init_message((&(req.cm)), REQ_ASK);
    req.cm.bm.size = sizeof(req);
    c->write_array(c,(char*) (&req), sizeof(connection_ask_req_message));
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

}

void connection_update_struct(connection *c, graph *g) {

}

void connection_ask_res(message *m, codes code) {
    connection_ask_res_message res;
    res.cm.bm = m->bm;
    res.cm.type = RES_ASK;
    res.code = code;

    m->c->write_array(m->c,(char*) &res, sizeof(connection_ask_res_message));
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

}

void connection_update_struct_res(message *m, codes code){

}