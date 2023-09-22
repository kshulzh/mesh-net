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

#ifndef MESH_NET_LIST_H
#define MESH_NET_LIST_H

#include "utils/predicate.h"

typedef struct {
    void *next;
    void *element;
} list_node;
typedef struct {
    list_node *first;
    list_node *last;
    unsigned int size;
} list;

#define for_each(l,type,body) \
                              \
    {               \
list_node* temp_node = l->first;       \
type * temp;\
while(temp_node) {                     \
    temp = (type *) temp_node->element;\
    body                        \
    temp_node = (list_node*) temp_node->next; \
}                             \
}                            \
                              \

void list_print(list*l) ;

list_node *new_list_node(void *element);

void list_add(list* l, void *element);

void* list_remove(list* l, int index);
void *list_remove_first(list* l);

void *list_remove_last(list* l);
list* new_list();

void *list_find_first(list* l, predicate* p);

void delete_list(list* l);

#endif //MESH_NET_LIST_H
