//
// Created by kirill on 28.09.23.
//

#include "services/route/handlers.h"
#include "services/route/messages.h"


message_handler* route_message_handlers() {
    static message_handler route_message_handlers[14];
    return route_message_handlers;
}

udp_handler* udp_handler1() {
    static udp_handler uh[1];
    return uh;
}

void route_handle_udp(message *m) {
    buffer b;
    buffer_init(&b, m->bm.size, m->bytes);
    route_udp_message *rum =  decode_route_udp_message(&b);
    instance * inst = m->c->r->inst;
    if (rum->index == rum->way->size) {
        if(udp_handler1()[0]!=0) {
            udp_handler1()[0](rum);
        }
    } else {
        rum->index++;
        connection * c = list_find_first(&inst->connections,connection_device_by_id(
                *((unsigned long *) list_get_by_id(rum->way, rum->index))));
        buffer_reset(&b);
        c->write_array(c,b.start,rum->rm.size);
    }
}

void route_handle(message*m) {
    route_message_handlers()[((route_message*)m->bytes)->type](m);
}

void route_setup() {
    message_handlers()[ROUTE] = route_handle;
    route_message_handlers()[UDP] = route_handle_udp;
}
