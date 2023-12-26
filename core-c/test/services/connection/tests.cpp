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
#include "services/connection/functions.h"
#include "io/buffer_utils.h"
}

buffer(ci1b1, 1028)
buffer(ci1b2, 1028)
buffer(ci1b3, 1028)
buffer(ci1bc, 1028)
buffer(ci2b1, 1028)
buffer(ci2b2, 1028)
buffer(ci2bc, 1028)
static int count = 0;

static void handler2(void *thiz, void *c) {
    count++;
    connection *con = (connection *) c;
    instance *inst = (instance *) con->r->inst;
    list_add(&inst->connections, con);
    list_add(&(inst->buffered_connections), new_connection_buffer(con));
    con->open(con);
}

static void handler1(void *thiz, void *c) {
    count++;
    connection *con = (connection *) c;
    instance *inst = (instance *) con->r->inst;
    list_add(&inst->connections, con);
    list_add(&(inst->buffered_connections), new_connection_buffer(con));
    con->open(con);
}

TEST(connection1, ask) {
    connection_setup();

    instance *inst1 = new_instance(new_device(1, 1));
    mock_radar *mr1 = (mock_radar *) new_mock_radar();
    instance_add_radar(inst1, mr1);
    mr1->r.on_find_device_handler = handler2;
    mock_connection *mc1 = new_mock_connection(create_buffers(4, 1000));
    list_add(&inst1->buffers, ci1b1);
    list_add(&inst1->buffers, ci1b2);
    list_add(&inst1->buffers, ci1b3);

    instance *inst2 = new_instance(new_device(2, 2));
    mock_radar *mr2 = (mock_radar *) new_mock_radar();
    mr2->r.on_find_device_handler = handler1;
    instance_add_radar(inst2, mr2);
    mock_connection *mc2 = new_mock_connection(create_buffers(4, 1000));
    list_add(&inst2->buffers, ci1b1);
    list_add(&inst2->buffers, ci1b2);
    list_add(&inst2->buffers, ci1b3);

    mock_connection_link(mc1, mc2);

    mock_radar_add_to_queue(mr1, &(mc1->c));
    mock_radar_add_to_queue(mr2, &(mc2->c));

    mr1->r.start(mr1);
    mr2->r.start(mr2);

    for (int i = 0; i < 8; i++) {
        instance_run(inst1);
        instance_run(inst2);
    }
    connection_ask(&(mc1->c));
    for (int i = 0; i < 8; i++) {
        instance_run(inst1);
        instance_run(inst2);
    }
    connection_get_struct(&(mc1->c));
    for (int i = 0; i < 8; i++) {
        instance_run(inst1);
        instance_run(inst2);
    }

    ASSERT_EQ(2, count);
    ASSERT_EQ(2, inst1->g->nodes.size);
}