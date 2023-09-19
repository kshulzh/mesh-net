//
// Created by kirill on 18.09.23.
//

#include <gtest/gtest.h>
#include "io/buffer.h"
#include "mock_connection.h"

TEST(mock_connection, test1) {
    char b1[100];
    char b2[100];
    buffer buf1;
    buffer buf2;
    buffer_init(&buf1, 100, b1);
    buffer_init(&buf2, 100, b2);
    mock_connection* mc1 = new_mock_connection(&buf1);
    mock_connection* mc2 = new_mock_connection(&buf1);
    mock_connection_link(mc1,mc2);
    mc1->c.open(mc1);
    mc2->c.open(mc2);
    mc1->c.write_array(mc1,"hello my name is Kirill",24);
    char b3[100];
    mc2->c.read_array(mc2,b3,24,0);
}