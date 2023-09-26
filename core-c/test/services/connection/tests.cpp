//
// Created by kirill on 24.09.23.
//
#include <gtest/gtest.h>

extern "C" {
#include "io/connection/connection_buffered.h"
#include "services/connection/handlers.h"
#include "io/connection/mock_radar.h"
#include "io/connection/mock_connection.h"
#include "services/connection/functions.h"
}

buffer(i1b1,128)
buffer(i1b2,128)
buffer(i1b3,128)
buffer(i1bc,128)
buffer(i2b1,128)
buffer(i2b2,128)
buffer(i2bc,128)
int count =0;
static void handler(void *thiz,void *c) {
    count++;
    connection* con = (connection*) c;
    instance *inst = (instance *) con->r->inst;
    list_add(&(inst->buffered_connections),new_connection_buffer(con));
    connection_ask(con);
}

static void handler1(void *thiz,void *c) {
    count++;
    connection* con = (connection*) c;
    instance *inst = (instance *) con->r->inst;
    list_add(&(inst->buffered_connections),new_connection_buffer(con));

}
TEST(connection, ask) {
    connection_setup();

    instance *inst1 = new_instance(new_device(1,1));
    mock_radar* mr1 =(mock_radar*) new_mock_radar();
    instance_add_radar(inst1, mr1);
    mr1->on_find_device_handler = handler;
    mock_connection* mc1 = new_mock_connection(i1bc);
    list_add(&inst1->buffers,i1b1);
    list_add(&inst1->buffers,i1b2);
    list_add(&inst1->buffers,i1b3);

    instance *inst2 = new_instance(new_device(2,2));
    mock_radar* mr2 =(mock_radar*) new_mock_radar();
    mr2->on_find_device_handler = handler1;
    instance_add_radar(inst2, mr2);
    mock_connection* mc2 = new_mock_connection(i2bc);
    list_add(&inst2->buffers,i1b1);
    list_add(&inst2->buffers,i1b2);
    list_add(&inst2->buffers,i1b3);

    mock_connection_link(mc1,mc2);

    mock_radar_add_to_queue(mr1,&(mc1->c));
    mock_radar_add_to_queue(mr2,&(mc2->c));

    mr1->r.start(mr1);
    mr2->r.start(mr2);

    instance_run(inst1);
    instance_run(inst2);
    instance_run(inst1);
    instance_run(inst2);
    instance_run(inst1);
    instance_run(inst2);
    instance_run(inst1);
    instance_run(inst2);
    ASSERT_EQ(2,count);
}