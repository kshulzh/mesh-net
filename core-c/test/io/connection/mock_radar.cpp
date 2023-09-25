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
#include "io/readers/readers.h"
#include "io/buffer.h"
#include "devices/device.h"
#include "io/connection/mock_radar.h"
#include "io/connection/mock_connection.h"
}

static mock_connection* mock_connection1 = new_mock_connection(0);
static mock_connection* mock_connection2 = new_mock_connection(0);
static mock_connection* mock_connection3 = new_mock_connection(0);
static int count = 0;

static void handler(void *thiz,void *connection) {
    count++;
}

TEST(mock_radar, test1) {
    mock_radar* m = (mock_radar*) new_mock_radar();
    m->on_find_device_handler = handler;
    mock_radar_add_to_queue(m,&(mock_connection1->c));
    mock_radar_add_to_queue(m,&(mock_connection2->c));
    mock_radar_add_to_queue(m,&(mock_connection3->c));
    m->r.start(m);

    mock_radar_find(m);
    ASSERT_EQ(1, count);
    mock_radar_find(m);
    ASSERT_EQ(2, count);
    mock_radar_find(m);
    ASSERT_EQ(3, count);
}
