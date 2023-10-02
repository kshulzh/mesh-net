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
#include "services/route/functions.h"
#include "services/route/handlers.h"
#include "services/route/messages.h"
#include "io/buffer_utils.h"
}
buffer(ri1b1, 1028)
buffer(ri1b2, 1028)
buffer(ri1b3, 1028)
buffer(ri1bc, 1028)
buffer(ri2b1, 1028)
buffer(ri2b2, 1028)
buffer(ri2bc, 1028)
static int count = 0;

static void handle_udp(route_udp_message *rum) {

    ASSERT_EQ('1', rum->msg->elements[0]);
    ASSERT_EQ('3', rum->msg->elements[2]);
}

static void handler2(void *thiz, void *c) {
    count++;
    connection *con = (connection *) c;
    con->d.id = 2;
    instance *inst = (instance *) con->r->inst;
    list_add(&inst->connections, con);
    list_add(&(inst->buffered_connections), new_connection_buffer(con));
    con->open(con);
}

static void handler1(void *thiz, void *c) {
    count++;
    connection *con = (connection *) c;
    con->d.id = 1;
    instance *inst = (instance *) con->r->inst;
    list_add(&inst->connections, con);
    list_add(&(inst->buffered_connections), new_connection_buffer(con));
    con->open(con);
}

TEST(route, ask) {
    connection_setup();
    route_setup();
    udp_handler1()[0] = handle_udp;

    instance *inst1 = new_instance(new_device(1, 1));
    mock_radar *mr1 = (mock_radar *) new_mock_radar();
    instance_add_radar(inst1, mr1);
    mr1->on_find_device_handler = handler2;
    mock_connection *mc1 = new_mock_connection(create_buffers(4, 1000));
    list_add(&inst1->buffers, ri1b1);
    list_add(&inst1->buffers, ri1b2);
    list_add(&inst1->buffers, ri1b3);

    instance *inst2 = new_instance(new_device(2, 2));
    mock_radar *mr2 = (mock_radar *) new_mock_radar();
    mr2->on_find_device_handler = handler1;
    instance_add_radar(inst2, mr2);
    mock_connection *mc2 = new_mock_connection(create_buffers(4, 1000));
    list_add(&inst2->buffers, ri1b1);
    list_add(&inst2->buffers, ri1b2);
    list_add(&inst2->buffers, ri1b3);

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

    route_udp(inst1, 2, "123", 3);
    for (int i = 0; i < 8; i++) {
        instance_run(inst1);
        instance_run(inst2);
    }

    ASSERT_EQ(2, count);
    ASSERT_EQ(2, inst1->g->nodes.size);
}