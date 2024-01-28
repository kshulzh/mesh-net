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
#include "io/connection/connection_buffered.h"
#include "services/connection/handlers.h"
#include "io/connection/mock_radar.h"
#include "io/connection/mock_connection.h"
#include "services/spread/handlers.h"
#include "services/spread/functions.h"
#include "services/connection/functions.h"
#include "io/buffer_utils.h"
}
static int count = 0;
static int handle_count = 0;

static void handle_udp(spread_udp_message *rum) {
    handle_count++;
    ASSERT_EQ('1', rum->msg->elements[0]);
    ASSERT_EQ('3', rum->msg->elements[2]);
}

static void handler1(void *thiz, void *c) {
    count++;
    connection *con = (connection *) c;
    con->open(con);
    connection_get_struct(con);
    instance *inst = (instance *) (con->r->inst);
    list_add(&(inst->connections), con);
    list_add(&(inst->buffered_connections), new_connection_buffer(con));
}

TEST(spread, ask) {
    connection_setup();
    spread_setup();
    spread_udp_handler1()[0] = handle_udp;

    instance *inst1 = new_instance(new_device(1, 1));
    mock_radar *mr1 = (mock_radar *) new_mock_radar();
    instance_add_radar(inst1, mr1);
    mr1->r.on_find_device_handler = handler1;
    mock_connection *mc1 = new_mock_connection(create_buffers(4, 1000));
    inst1->buffers = *create_buffers(5, 1500);

    instance *inst2 = new_instance(new_device(2, 2));
    mock_radar *mr2 = (mock_radar *) new_mock_radar();
    mr2->r.on_find_device_handler = handler1;
    instance_add_radar(inst2, mr2);
    mock_connection *mc2 = new_mock_connection(create_buffers(4, 1000));
    mock_connection *mc2_3 = new_mock_connection(create_buffers(4, 1000));
    inst2->buffers = *create_buffers(5, 1500);

    instance *inst3 = new_instance(new_device(3, 3));
    mock_radar *mr3 = (mock_radar *) new_mock_radar();
    mr3->r.on_find_device_handler = handler1;
    instance_add_radar(inst3, mr3);
    mock_connection *mc3 = new_mock_connection(create_buffers(4, 1000));
    inst3->buffers = *create_buffers(5, 1500);

    mock_connection_link(mc1, mc2);
    mock_connection_link(mc2_3, mc3);

    mock_radar_add_to_queue(mr1, mc2);
    mock_radar_add_to_queue(mr2, mc1);

    mock_radar_add_to_queue(mr3, mc2_3);
    mock_radar_add_to_queue(mr2, mc3);

    mr1->r.start(mr1);
    mr2->r.start(mr2);
    mr3->r.start(mr3);

    for (int i = 0; i < 16; i++) {
        instance_run(inst1);
        instance_run(inst2);
        instance_run(inst3);
    }

    spread_udp(inst1, (uint8_t *) "123", 3);
    for (int i = 0; i < 8; i++) {
        instance_run(inst1);
        instance_run(inst2);
        instance_run(inst3);
    }

    ASSERT_EQ(2, handle_count);
    ASSERT_EQ(3, inst3->g->nodes.size);
    ASSERT_EQ(3, inst2->g->nodes.size);
    ASSERT_EQ(3, inst1->g->nodes.size);
}

TEST(spread, link_graph) {
    connection_setup();
    spread_setup();
    spread_udp_handler1()[0] = handle_udp;

    instance *inst1 = new_instance(new_device(1, 1));
    mock_radar *mr1 = (mock_radar *) new_mock_radar();
    instance_add_radar(inst1, mr1);
    mr1->r.on_find_device_handler = handler1;
    mock_connection *mc1 = new_mock_connection(create_buffers(4, 1000));
    inst1->buffers = *create_buffers(5, 1500);

    instance *inst2 = new_instance(new_device(2, 2));
    mock_radar *mr2 = (mock_radar *) new_mock_radar();
    mr2->r.on_find_device_handler = handler1;
    instance_add_radar(inst2, mr2);
    mock_connection *mc2 = new_mock_connection(create_buffers(4, 1000));
    mock_connection *mc2_3 = new_mock_connection(create_buffers(4, 1000));
    inst2->buffers = *create_buffers(5, 1500);

    instance *inst3 = new_instance(new_device(3, 3));
    mock_radar *mr3 = (mock_radar *) new_mock_radar();
    mr3->r.on_find_device_handler = handler1;
    instance_add_radar(inst3, mr3);
    mock_connection *mc3 = new_mock_connection(create_buffers(4, 1000));
    inst3->buffers = *create_buffers(5, 1500);

    mock_connection_link(mc1, mc2);
    mock_connection_link(mc2_3, mc3);

    mock_radar_add_to_queue(mr1, mc2);
    mock_radar_add_to_queue(mr2, mc1);

    mock_radar_add_to_queue(mr3, mc2_3);
    mock_radar_add_to_queue(mr2, mc3);

    mr1->r.start(mr1);
    mr2->r.start(mr2);
    mr3->r.start(mr3);

    for (int i = 0; i < 16; i++) {
        instance_run(inst1);
        instance_run(inst2);
        instance_run(inst3);
    }

    for (int i = 0; i < 8; i++) {
        instance_run(inst1);
        instance_run(inst2);
        instance_run(inst3);
    }

    ASSERT_EQ(3, inst3->g->nodes.size);
}