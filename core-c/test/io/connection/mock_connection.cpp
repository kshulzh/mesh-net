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
#include "io/buffer.h"
#include "io/connection/mock_connection.h"
}

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
    mc2->c.read_array(mc2,b3,90,0);
    printf("%s",b3);
}