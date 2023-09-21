//
// Created by kirill on 18.09.23.
//

extern "C" {
#include "io/readers/readers.h"
#include "io/buffer.h"
}

#include <gtest/gtest.h>
#include "devices/device.h"
#include "mock_radar.h"
#include "mock_connection.h"

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

    mock_radar_find(m);
    ASSERT_EQ(1, count);
    mock_radar_find(m);
    ASSERT_EQ(2, count);
    mock_radar_find(m);
    ASSERT_EQ(3, count);
}
