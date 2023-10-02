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


#include <gtest/gtest.h>

extern "C" {
#include "devices/device.h"
#include "model/graph.h"
}

device *d1 = new_device(1, 1);
device *d2 = new_device(2, 2);
device *d3 = new_device(3, 3);
device *d4 = new_device(4, 4);
device *d5 = new_device(5, 5);
buffer(t1, 1024)
TEST(graph, test1) {
    graph *g1 = new_graph(d1);
    g1->equals = predicate_device_equals;
    graph *g2 = new_graph(d2);
    g2->equals = predicate_device_equals;
    graph *g3 = new_graph(d3);
    g3->equals = predicate_device_equals;
    graph *g4 = new_graph(d4);
    g4->equals = predicate_device_equals;
    graph *g5 = new_graph(d5);
    g5->equals = predicate_device_equals;

    graph_add_graph(g1, (&(g1->this_node)), g2);
    graph_add_graph(g1, (&(g2->this_node)), g3);
    graph_add_graph(g1, (&(g3->this_node)), g4);
    graph_add_graph(g1, (&(g3->this_node)), g5);

    ASSERT_EQ(graph_find_way_in_depth(g1, (&(g1->this_node)), device_equals(d5), 0)->size, 4);
    g1->encode = encode_device;
    encode_graph(t1, g1);
    buffer_reset(t1);
    graph *g6 = decode_graph(t1, decode_device, 0);

    ASSERT_EQ(graph_find_way_in_depth(g6, (&(g6->this_node)), device_equals(d5), 0)->size, 4);
    g6->equals = predicate_device_equals;
    g6->encode = encode_device;
    g6->e_free = 0;

    graph_unlink_nodes(g6, graph_find_node_by_value(g6, d2), graph_find_node_by_value(g6, d3));
    ASSERT_EQ(graph_find_way_in_depth(g6, (&(g6->this_node)), device_equals(d5), 0), nullptr);
    ASSERT_EQ(g6->nodes.size, 2);
}