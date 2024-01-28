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

#include <gtest/gtest.h>

extern "C" {
#include "../../src/headers/containers/list.h"
}

TEST(list, add) {
    list *l = new_list();
    int e1 = 1;
    int e2 = 2;
    int e3 = 3;
    list_add(l, &e1);
    list_add(l, &e2);
    list_add(l, &e3);
    ASSERT_EQ(&e3, ((list_node *) l->last)->element);
    ASSERT_EQ(&e1, ((list_node *) l->first)->element);
}

TEST(list, remove) {
    list *l = new_list();
    int e1 = 1;
    int e2 = 2;
    int e3 = 3;
    list_add(l, &e1);
    list_add(l, &e2);
    list_add(l, &e3);
    list_remove(l, 2);
    ASSERT_EQ(&e2, ((list_node *) l->last)->element);
    ASSERT_EQ(&e1, ((list_node *) l->first)->element);
    list_remove_first(l);
    ASSERT_EQ(&e2, ((list_node *) l->last)->element);
    ASSERT_EQ(&e2, ((list_node *) l->first)->element);
    list_add(l, &e1);
    list_add(l, &e3);
    list_remove(l, 1);
    ASSERT_EQ(&e3, ((list_node *) l->last)->element);
    ASSERT_EQ(&e2, ((list_node *) l->first)->element);
}