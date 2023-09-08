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

#include <cstdlib.h>

typedef struct {
    void *next;
    void *element;
} list_node;
typedef struct {
    list_node *first;
    list_node *last;

} list;

void list_print(list*l) {
    list_node * temp = l->first;
    while (temp) {
        printf("%x\n",temp->element);
        temp = (list_node*) temp->next;
    }
}

list_node *new_list_node(void *element) {
    list_node * temp = (list_node*) malloc(sizeof(list_node));
    temp->next = 0;
    temp->element = element;
    return temp;
}

void list_add(list* l, void *element) {
    list_node * temp = new_list_node(element);
    if (l->first == 0) {
        l->first = temp;
        l->last = l->first;
    } else {
        l->last->next = temp;
        l->last = temp;
    }
}

void* list_remove(list* l, int index) {
    list_node *temp = l->first;
    if(l->first == 0) {
        return 0;
    }
    if(index == 0) {
        l->first = (list_node*) l->first->next;
    } else {
        int i;
        for (i = 1; i < index && temp->next!=0; ++i, temp = (list_node*) temp->next);
        if(temp->next!=0 && index == i) {
            list_node *temp1 = (list_node*) temp->next;
            if(((list_node*) temp->next)->next == 0) {
                l->last = temp;
                temp->next = 0;
            } else {
                temp->next = temp1->next;
            }
            temp = temp1;
        } else {
            return 0;
        }
    }
    void * element = temp->element;
    delete temp;
    return element;
}
void *list_remove_first(list* l) {
    return list_remove(l,0);
}

list* new_list() {
    list* temp = (list*) malloc(sizeof(list));
    temp->last = 0;
    temp->first = 0;
    return temp;
}

#endif //MESH_NET_LIST_H
