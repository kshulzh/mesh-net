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

#include "services/route/handlers.h"
#include "services/route/messages.h"
#include "log/connection_logger.h"


message_handler *route_message_handlers() {
    static message_handler route_message_handlers[14];
    return route_message_handlers;
}

udp_handler *udp_handler1() {
    static udp_handler uh[1];
    return uh;
}

void route_handle_udp(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    route_udp_message *rum = decode_route_udp_message(&b);
    instance *inst = m->c->r->inst;
    if (rum->index == rum->way->size) {
        CONNECTION_LOG_DEBUG(m->c, "Received message:\"%.*s\" from id:%llu", rum->msg->size, rum->msg->elements,
                             *((uint64_t *) rum->way->first->element));
        if (udp_handler1()[0] != 0) {
            udp_handler1()[0](rum);
        } else {
            CONNECTION_LOG_WARN(m->c, "Received message:\"%.*s\" from id:%llu unhandled", rum->msg->size,
                                rum->msg->elements, *((uint64_t *) rum->way->first->element));
        }
    } else {
        rum->index++;
        connection *c = list_find_first(&inst->connections, connection_device_by_id(
                *((uint64_t *) list_get_by_id(rum->way, rum->index))));
        if (c) {
            CONNECTION_LOG_ERROR(c, "Next connection not found for message:\"%.*s\" from id:%llu to id:%llu",
                                 rum->msg->size, rum->msg->elements, *((uint64_t *) rum->way->first->element),
                                 *((uint64_t *) rum->way->last->element));
            //todo
            return;
        }
        buffer_reset(&b);
        CONNECTION_LOG_DEBUG(c, "Sending message:\"%.*s\" from id:%llu to id:%llu", rum->msg->size, rum->msg->elements,
                             *((uint64_t *) rum->way->first->element), *((uint64_t *) rum->way->last->element));
        c->write_array(c, b.start, rum->rm.bm.size);
    }
}

void route_handle(message *m) {
    route_message *rm = ((route_message *) m->bytes);
    route_message_handlers()[rm->type](m);
}

void route_setup() {
    message_handlers()[ROUTE] = route_handle;
    route_message_handlers()[UDP] = route_handle_udp;
}
