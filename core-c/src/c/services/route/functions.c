

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

#include "model/instance.h"

#include "services/route/messages.h"
#include "services/route/functions.h"
#include "services/route/handlers.h"
#include "services/utils.h"

void route_udp(instance *inst, uint64_t id, uint8_t *msg, uint32_t size) {
    char b[1500];
    buffer b1;
    buffer_init(&b1,1500,b);
    array_char ac;
    ac.size = size;
    ac.elements = msg;

    route_udp_message* rum = mem_alloc(sizeof(route_udp_message));
    rum->msg = &ac;
    rum->index = 1;
    rum->rm.type = UDP;
    rum->rm.bm.type = ROUTE;
    list *l = graph_find_way_in_depth(inst->g, graph_find_node_by_value(inst->g, &(inst->this_device)),
                                      connection_device_by_id(id), 0);
    list *ml = new_list();
    for_each(l, graph_node, {
        list_add(ml, temp->element);
    })
    delete_list(l, 0, 0);
    rum->way = ml;
    if (rum->index == rum->way->size) {
        rum->inst = inst;
        if (udp_handler1()[0] != 0) {
            udp_handler1()[0](&rum);
        }
    } else {
        uint64_t *id1 = ((uint64_t *) list_get_by_id(rum->way, rum->index));
        rum->index++;
        buffer_reset(&b1);
        encode_route_udp_message(&b1, rum);
        rum->rm.bm.size = buffer_message_set_size(&b1);
        connection *c = list_find_first(&inst->connections, connection_device_by_id(
                *id1));
        buffer_reset(&b1);
        if (c != 0) {
            c->write_array(c, b1.start, rum->rm.bm.size);
        }
    }
}