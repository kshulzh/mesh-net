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

#ifndef MESH_NET_LIST_H
#define MESH_NET_LIST_H

#include "utils/predicate.h"
#include "io/buffer.h"

typedef struct {
    void *next;
    void *element;
} list_node;
typedef struct {
    list_node *first;
    list_node *last;
    uint32_t size;
} list;

#define for_each(l, type, body) \
                              \
    {               \
list_node* temp_node = l->first;       \
type * temp;\
while(temp_node) {                     \
    temp = (type *) temp_node->element;\
    body                        \
    temp_node = (list_node*) temp_node->next; \
}                             \
}

#define for_each1(l, type, body) \
                              \
    {               \
list_node* temp_node1 = l->first;       \
type * temp1;\
while(temp_node1) {                     \
    temp1 = (type *) temp_node1->element;\
    body                        \
    temp_node1 = (list_node*) temp_node1->next; \
}                             \
}

void list_print(list *l);

list_node *new_list_node(void *element);

void list_add(list *l, void *element);

void *list_remove(list *l, int index);

void *list_remove_first(list *l);

void *list_remove_last(list *l);

list *new_list();

void *list_find_first(list *l, predicate *p);

void *list_get_by_id(list *l, int index);

void delete_list(list *l, void (*free)(void *), char save_list);

void list_remove_if(list *l, predicate *p, void (*efree)(void *));

void encode_list(buffer *b, list *l, void (*encoder)(buffer *b, void *));

//predicate *list_id(unsigned int id);

void list_reset(list *l);

list *decode_list(buffer *b, void *(*decoder)(buffer *b));

#endif //MESH_NET_LIST_H
