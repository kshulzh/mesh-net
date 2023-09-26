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
#include "io/buffer.h"

typedef struct {
    void *element;
    list near;
    unsigned int index;
    void *g;
} graph_node;

typedef struct {
    //list of graph_nodes
    list nodes;

    graph_node this_node;

    char (*equals)(void *obj1, void *obj2);

    void (*encode)(buffer *, void *e);

    void (*e_free)(void *);
} graph;


//returns list of graph_nodes
list *graph_find_way_in_depth(graph *l, graph_node *this_node, predicate *p, list *checked);

graph_node *new_graph_node(void *element);

graph *new_graph(void *element);

void graph_add_graph(graph *thiz, graph_node *gn1, graph *other);

void graph_link_nodes(graph *thiz, graph_node *gn1, graph_node *gn2);

graph_node *graph_find_node_by_value(graph *thiz, void *element);

void encode_graph(buffer *b, graph *gr);

graph *decode_graph(buffer *b, void *(*decode)(buffer *b));

void graph_check_links(graph *g);

void graph_unlink_nodes(graph *thiz, graph_node *gn1, graph_node *gn2);

#endif //MESH_NET_GRAPH_H
