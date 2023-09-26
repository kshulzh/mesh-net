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

#include <stdlib.h>
#include "containers/list.h"

void list_print(list *l) {
    list_node *temp = l->first;
    while (temp) {
        //printf("%x\n",temp->element);
        temp = (list_node *) temp->next;
    }
}

list_node *new_list_node(void *element) {
    list_node *temp = (list_node *) malloc(sizeof(list_node));
    temp->next = 0;
    temp->element = element;
    return temp;
}

void list_add(list *l, void *element) {
    list_node *temp = new_list_node(element);
    if (l->first == 0) {
        l->first = temp;
        l->last = l->first;
    } else {
        l->last->next = temp;
        l->last = temp;
    }
    l->size++;
}

void *list_remove(list *l, int index) {
    list_node *temp = l->first;
    if (l->first == 0) {
        return 0;
    }
    if (index == 0) {
        l->first = (list_node *) l->first->next;
    } else {
        int i;
        for (i = 1; i < index && temp->next != 0; ++i, temp = (list_node *) temp->next);
        if (temp->next != 0 && index == i) {
            list_node *temp1 = (list_node *) temp->next;
            if (((list_node *) temp->next)->next == 0) {
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
    void *element = temp->element;
    free(temp);
    l->size--;
    return element;
}

void *list_remove_first(list *l) {
    return list_remove(l, 0);
}

void *list_remove_last(list *l) {
    return list_remove(l, l->size - 1);
}

list *new_list() {
    list *temp = (list *) malloc(sizeof(list));
    temp->last = 0;
    temp->first = 0;
    temp->size = 0;
    return temp;
}

void *list_find_first(list *l, predicate *p) {
    list_node *temp = l->first;
    while (temp != 0) {
        if (is(p, temp->element)) {
            return temp->element;
        }
        temp = (list_node *) temp->next;
    }

    return 0;
}

void delete_list(list *l,void (*efree)(void *),char save_list) {
    list_node *temp = l->first;
    list_node *next;

    if (temp != 0) {
        next = (list_node *) temp->next;
        while (next != 0) {
            if(efree != 0) {
                efree(temp->element);
            }
            free(temp);
            temp = next;
            next = (list_node *) temp->next;
        }
    }

    if(save_list == 0) {
        free(l);
    }
}

void encode_list(buffer *b, list *l, void (*encoder)(buffer *b, void *)) {
    write_to_buffer(b, &(l->size), sizeof(unsigned int));
    for_each(l, void, {
        encoder(b, temp);
    })
}

list *decode_list(buffer *b, void *(*decode)(buffer *b)) {
    list *l = new_list();
    unsigned int size = *((int *) read_from_buffer(b, sizeof(unsigned int)));
    for (int i = 0; i < size; ++i) {
        list_add(l, decode(b));
    }

    return l;
}

void list_remove_if(list* l, predicate *p,void (*efree)(void *)) {
    list* l1 = new_list();
    for_each(l,void, {
        if(is(p,temp) == 0) {
            list_add(l1,temp);
        } else {
            if(efree) {
                efree(temp);
            }
        }
    })
    l->first = l1->first;
    l->last = l1->last;
    l->size = l1->size;
    free(l1);
}