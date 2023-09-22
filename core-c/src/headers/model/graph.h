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

#ifndef MESH_NET_GRAPH_H
#define MESH_NET_GRAPH_H

#include "containers/list.h"
#include "utils/predicate.h"
#include "devices/device.h"
#include "utils/new.h"

typedef struct {
    void *element;
    list near;
} graph_node;

typedef struct {
    //list of graph_nodes
    list nodes;

    graph_node this_node;
} graph;


//returns list of graph_nodes
list *graph_find_way_in_depth(graph* l, graph_node *this_node, predicate* p, list *checked) {
    if(checked == nullptr) {
        checked = new_list();

    }
    list_add(checked,this_node);

    if(is(p,this_node->element)) {
        return checked;
    }

    for_each(this_node->near, graph_node, {
        list *list1 = graph_find_way_in_depth(l,temp,p,checked);
        if(list1!=0) {
            return checked;
        }
    })

    list_remove_last(checked);

    return nullptr;
}
graph_node * new_graph_node(void *element) {
    graph_node *g = New(graph_node);
    return g;

}

graph* new_graph(void *element) {
    graph *g = New(graph);
    g->this_node = new_graph_node(element);
    list_add((&(g->nodes)),g->this_node);
    return g;
}

void graph_add_graph(graph* thiz, graph* other, char (*equals)(void*,void*)) {
    //todo
}



#endif //MESH_NET_GRAPH_H
