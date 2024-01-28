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

#include "services/spread/functions.h"
#include "services/spread/messages.h"
#include "services/utils.h"
#include "log/connection_logger.h"
#include "log/instance_logger.h"

static uint8_t id = 0;

void spread_udp(instance *c, uint8_t *msg, uint32_t size) {
    spread_udp_message sum;
    sum.sm.bm.type = SPREAD;
    sum.sm.bm.message_id = (c->this_device.id << 8) | id++;
    sum.sm.type = UDP;
    array_char ac;
    ac.size = size;
    ac.elements = msg;
    sum.msg = &ac;
    sum.src_id = c->this_device.id;
    buffer *b = list_find_first(&c->buffers, buffer_is_free());

    if (b != 0) {
        b->is_locked = 1;
        buffer_reset(b);
        encode_spread_udp_message(b, &sum);
        sum.sm.bm.size = buffer_message_set_size(b);
        INSTANCE_LOG_DEBUG(c, "Sending spread udp message:\"%.*s\" to all", size, msg);
        spread_all(&(c->connections), b->start, b->temp - b->start, 0, 0);
        b->is_locked = 0;
    }
}

void spread_all(list *connections, uint8_t *data, uint32_t size_data, uint64_t *exclude, uint32_t size_exclude) {
    for_each(connections, connection, {
        uint8_t included = 1;
        for (int j = 0; j < size_exclude; ++j) {
            if (exclude[j] == temp->d.id) {
                included = 0;
                break;
            }
        }

        if (included) {
            CONNECTION_LOG_DEBUG(temp, "Sending spread message size:%d to id:%llu", size_data, temp->d.id);
            temp->write_array(temp, data, size_data);
        }
    })
}

void spread_res(message *m) {
    instance *i = m->c->r->inst;
    spread_all(&(i->connections), m->bytes, m->bm.size, &(m->c->d.id), 1);
}

void spread_link(instance *c, uint64_t id2) {
    spread_link_message slm;
    slm.sm.bm.size = sizeof(spread_link_message);
    slm.sm.bm.type = SPREAD;
    slm.sm.bm.message_id = (c->this_device.id << 8) | id++;
    slm.sm.type = LINK;
    slm.id1 = c->this_device.id;
    slm.id2 = id2;

    INSTANCE_LOG_DEBUG(c, "Sending spread link message id2:%llu to all except id:%llu", id2, id2);
    spread_all(&(c->connections), (uint8_t *) &slm, slm.sm.bm.size, &id2, 1);
}

void spread_link_graph(instance *c, graph *g) {
    spread_link_graph_message slgm;
    slgm.sm.bm.size = sizeof(spread_link_message);
    slgm.sm.bm.type = SPREAD;
    slgm.sm.bm.message_id = (c->this_device.id << 8) | id++;
    slgm.sm.type = LINK_GRAPH;
    slgm.id1 = c->this_device.id;
    slgm.g = g;
    buffer *b = list_find_first(&c->buffers, buffer_is_free());

    if (b != 0) {
        b->is_locked = 1;
        buffer_reset(b);
        encode_spread_link_graph_message(b, &slgm);
        slgm.sm.bm.size = buffer_message_set_size(b);
        INSTANCE_LOG_DEBUG(c, "Sending spread link message graph nodes count:%d to all except id:%llu", g->nodes.size,
                           &(((device *) g->this_node.element)->id));
        spread_all(&(c->connections), b->start, b->temp - b->start, &(((device *) g->this_node.element)->id), 1);
        b->is_locked = 0;
    }
}

void spread_unlink(instance *c, uint64_t id1, uint64_t id2) {
    //todo
}

