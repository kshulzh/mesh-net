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

#include "model/graph.h"
#include "utils/new.h"
#include "services/utils.h"

list *graph_find_way_in_depth(graph *l, graph_node *this_node, predicate *p, list *checked) {
    if (checked == 0) {
        checked = new_list();
    }
    list_add(checked, this_node);

    if (is(p, this_node->element)) {
        return checked;
    }
    for_each((&(this_node->near)), graph_node, {
        predicate *eq = equals(temp);
        if (list_find_first(checked, eq) == 0) {
            list *list1 = graph_find_way_in_depth(l, temp, p, checked);
            if (list1 != 0) {
                return checked;
            }
        }
        mem_free(eq);
    })

    list_remove_last(checked);

    return 0;
}

graph_node *new_graph_node(void *element) {
    graph_node *g = New(graph_node);
    g->near.first = 0;
    g->near.size = 0;
    g->near.last = 0;
    g->element = element;

    return g;
}

graph *new_graph(void *element) {
    graph *g = New(graph);
    g->this_node = *new_graph_node(element);
    g->nodes.first = 0;
    g->nodes.size = 0;
    g->nodes.last = 0;
    g->this_node.g = g;
    g->e_free = 0;
    g->encode = 0;
    g->equals = 0;
    list_add((&(g->nodes)), &(g->this_node));

    return g;
}

void graph_add_graph(graph *thiz, graph_node *gn1, graph *other) {
    if (gn1 == 0) {
        gn1 = &(thiz->this_node);
    }
    for_each((&(other->nodes)), graph_node, {
        graph_node *gn2 = graph_find_node_by_value(thiz, temp->element);
        if (gn2 == 0) {
            temp->g = thiz;
            list_add(&thiz->nodes, temp);
        } else {
            //todo
        }
    });
    graph_link_nodes(thiz, gn1, &(other->this_node));
}

void graph_link_nodes(graph *thiz, graph_node *gn1, graph_node *gn2) {
    graph_node *gn3 = graph_find_node_by_value(thiz, gn2->element);
    if (gn3 == 0) {
        list_add(&thiz->nodes, gn2);
    }
    list_add(&gn1->near, gn2);
    list_add(&gn2->near, gn1);
}

graph_node *graph_find_node_by_value(graph *thiz, void *element) {
    for_each((&(thiz->nodes)), graph_node, {
        if (thiz->equals(element, temp->element)) {
            return temp;
        }
    });

    return 0;
}

void encode_graph_node_index(buffer *b, void *gn) {
    //write_int_to_buffer(b,((graph_node *) gn)->index);
    write_dump(b, &(((graph_node *) gn)->index), sizeof(uint32_t));
}

void encode_graph(buffer *b, graph *gr) {
    //write_int_to_buffer(b,(gr->nodes).size);
    write_dump(b, &((gr->nodes).size), sizeof(uint32_t));
    int i = 0;
    for_each((&(gr->nodes)), graph_node, {
        temp->index = i;
        gr->encode(b, temp->element);
        i++;
    })

    for_each((&(gr->nodes)), graph_node, {
        encode_list(b, &temp->near, encode_graph_node_index);
    })
}

graph *decode_graph(buffer *b, void *(*decode)(buffer *b), void *(*clone1)(void *)) {
    uint32_t size = *((uint32_t *) read_dump_and_get(b, sizeof(uint32_t)));
    void **decoded = mem_alloc(sizeof(void *) * size);
    if (clone1 == 0) {
        clone1 = empty_clone;
    }
    graph *g = new_graph(clone1(decode(b)));
    decoded[0] = &g->this_node;
    for (int i = 1; i < size; ++i) {
        graph_node *t = new_graph_node(clone1(decode(b)));
        t->g = g;
        decoded[i] = t;
        list_add(&g->nodes, decoded[i]);
    }
    for_each((&(g->nodes)), graph_node, {
        list *indexes = decode_list(b, decode_uint32);
        for_each1(indexes, uint32_t, {
                          list_add(&temp->near, decoded[*((uint32_t *) temp1)]);
                  })
        //delete_list(indexes, 0, 0);
    })
    mem_free(decoded);

    return g;
}

char predicate_graph_node_index(void *thiz, void *params) {
    return ((graph_node *) thiz)->index == params;
}

predicate *graph_node_index(unsigned int i) {
    return new_predicate(predicate_graph_node_index, (void *) i);
}

void free_graph_node(void *gh) {
    graph_node *thiz = (graph_node *) gh;
    delete_list(&(thiz->near), 0, 1);
    if (((graph *) thiz->g)->e_free) {
        ((graph *) thiz->g)->e_free(thiz->element);
    }
    mem_free(thiz);
}

void graph_node_mark(graph_node *gn) {
    if (gn->index == 0) {
        return;
    }
    gn->index = 0;
    for_each((&(gn->near)), graph_node, {
        graph_node_mark(temp);
    })
}

void graph_check_links(graph *g) {
    for_each((&(g->nodes)), graph_node, {
        temp->index = -1;
    })

    graph_node_mark(&g->this_node);

    list_remove_if(&g->nodes, graph_node_index(-1), free_graph_node);
}

void graph_unlink_nodes(graph *thiz, graph_node *gn1, graph_node *gn2) {

    list_remove_if(&gn1->near, equals(gn2), 0);
    list_remove_if(&gn2->near, equals(gn1), 0);
    graph_check_links(thiz);
}