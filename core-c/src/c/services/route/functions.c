//
// Created by kirill on 28.09.23.
//

#include <stdio.h>
#include "model/instance.h"

#include "services/route/messages.h"
#include "services/route/functions.h"
#include "services/route/handlers.h"
#include "services/utils.h"
#include "log/logger.h"

void route_udp(instance *inst, unsigned long id, char *msg, unsigned int size) {
    buffer(b1,1024)
    array_char ac;
    ac.size = size;
    ac.elements = msg;

    route_udp_message rum;
    rum.msg = &ac;
    rum.index = 1;
    rum.rm.type = ROUTE;
    list* l= graph_find_way_in_depth(inst->g, graph_find_node_by_value(inst->g,&(inst->this_device)), connection_device_by_id(id),0);
    list* ml = new_list();
    for_each(l,graph_node,{
        list_add(ml,temp->element);
    })
    delete_list(l,0,0);
    rum.way = ml;
    encode_route_udp_message(b1,&rum);
    buffer_message_set_size(b1);
    if (rum.index == rum.way->size) {
        rum.inst = inst;
        if(udp_handler1()[0]!=0) {
            udp_handler1()[0](&rum);
        }
    } else {
        unsigned long *id1 = ((unsigned long *) list_get_by_id(rum.way, rum.index));
        rum.index++;
        connection * c = list_find_first(&inst->connections,connection_device_by_id(
                *id1));
        buffer_reset(b1);
        if(c != 0) {
            c->write_array(c,b1->start,rum.rm.size);
        }
    }
}