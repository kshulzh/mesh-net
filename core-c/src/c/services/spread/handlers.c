#include "services/spread/handlers.h"
#include "services/spread/functions.h"

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

uint32_t ids[256];
uint8_t temp;

message_handler *spread_message_handlers() {
    static message_handler spread_message_handlers[14];
    return spread_message_handlers;
}

spread_udp_handler *spread_udp_handler1() {
    static spread_udp_handler uh[1];
    return uh;
}

void spread_handle_link(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    spread_link_message *slm = decode_spread_link_message(&b);
    for (int i = 0; i < 256; i++) {
        if (ids[i] == slm->sm.bm.message_id) {
            return;
        }
    }
    instance *inst = m->c->r->inst;
    device d1;
    device d2;
    d1.id = slm->id1;
    d2.id = slm->id2;

    graph_link_nodes(inst->g, graph_find_node_by_value(inst->g, &d1), graph_find_node_by_value(inst->g, &d2));

    spread_res(m);
}

void spread_handle_link_graph(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    spread_link_graph_message *slgm = decode_spread_link_graph_message(&b);
    for (int i = 0; i < 256; i++) {
        if (ids[i] == slgm->sm.bm.message_id) {
            return;
        }
    }
    instance *inst = m->c->r->inst;
    device d1;
    d1.id = slgm->id1;

    graph_add_graph(inst->g, graph_find_node_by_value(inst->g, &d1), slgm->g);

    spread_res(m);
}

void spread_handle_udp(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    spread_udp_message *sum = decode_spread_udp_message(&b);
    for (int i = 0; i < 256; i++) {
        if (ids[i] == sum->sm.bm.message_id) {
            return;
        }
    }

    if (spread_udp_handler1()) {
        spread_udp_handler1()[0](sum);
    }

    spread_res(m);
}

void spread_handle(message *m) {
    buffer b1;
    buffer_init(&b1, 100, m->bytes);
    spread_message rm = *decode_spread_message(&b1);
    spread_message_handlers()[rm.type](m);
}


void spread_setup() {
    message_handlers()[SPREAD] = spread_handle;
    spread_message_handlers()[UDP] = spread_handle_udp;
    spread_message_handlers()[LINK] = spread_handle_link;
    spread_message_handlers()[LINK_GRAPH] = spread_handle_link_graph;

    for (int i = 0; i < 256; i++) {
        ids[i] = 0;
    }
}