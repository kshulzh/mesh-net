/*
 * Copyright (c) 2024. Kirill Shulzhenko
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

#include "services/spread/handlers.h"
#include "services/spread/functions.h"
#include "log/connection_logger.h"
#include "log/instance_logger.h"

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

    CONNECTION_LOG_DEBUG(m->c, "Linking nodes id1:%d and id2:%d", d1.id, d2.id);
    graph_link_nodes(inst->g, graph_find_node_by_value(inst->g, &d1), graph_find_node_by_value(inst->g, &d2));

    INSTANCE_LOG_DEBUG(m->c->r->inst, "Spread linking nodes id1:%d and id2:%d", d1.id, d2.id);
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

    CONNECTION_LOG_DEBUG(m->c, "Linking graph to id1:%d with nodes count:%d", d1.id, slgm->g->nodes.size);
    graph_add_graph(inst->g, graph_find_node_by_value(inst->g, &d1), slgm->g);

    CONNECTION_LOG_DEBUG(m->c, "Spread linking graph to id1:%d with nodes count:%d", d1.id, slgm->g->nodes.size);
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
    } else {
        CONNECTION_LOG_WARN(m->c, "Received spread udp message:\"%.*s\" from id:%d unhandled", sum->msg->size,
                            sum->msg->elements, sum->src_id);
    }

    INSTANCE_LOG_DEBUG(m->c->r->inst, "Spread udp message:\"%.*s\" from id:%d ", sum->msg->size, sum->msg->elements,
                       sum->src_id);
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