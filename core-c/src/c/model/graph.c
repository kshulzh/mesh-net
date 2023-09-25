//
// Created by kirill on 24.09.23.
//

//returns list of graph_nodes

#include "model/graph.h"
#include "devices/device.h"
#include "utils/new.h"

list *graph_find_way_in_depth(graph* l, graph_node *this_node, predicate* p, list *checked) {
    if(checked == 0) {
        checked = new_list();

    }
    list_add(checked,this_node);

    if(is(p,this_node->element)) {
        return checked;
    }

    for_each((&(this_node->near)), graph_node, {
            list *list1 = graph_find_way_in_depth(l,temp,p,checked);
            if(list1!=0) {
                return checked;
            }
    })

    list_remove_last(checked);

    return 0;
}
graph_node * new_graph_node(void *element) {
    graph_node *g = New(graph_node);
    return g;

}

graph* new_graph(void *element) {
    graph *g = New(graph);
    g->this_node = *new_graph_node(element);
    list_add((&(g->nodes)),&(g->this_node));
    return g;
}

void graph_add_graph(graph* thiz, graph* other, char (*equals)(void*,void*)) {
    //todo
}