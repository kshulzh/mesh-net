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
}

TEST(reader, read_char) {
    char b[1];
    buffer buf;
    buffer_init(&buf, 1, b);
    b[0] = 'c';

    char expected_char = 'c';
    char result_char =*read_char(&buf);
    ASSERT_EQ(expected_char, result_char);
}
TEST(reader, read_int) {
    int b[1];
    buffer buf;
    buffer_init(&buf, 1, reinterpret_cast<char *>(b));
    b[0] = 123456789;

    int expected_int = 123456789;
    int result_int =*read_int(&buf);
    ASSERT_EQ(expected_int, result_int);
}

TEST(reader, read_int_array) {
    char c[sizeof(array_int)+ sizeof(int)*3];
    buffer buf;
    buffer_init(&buf, sizeof(array_int)+ sizeof(int)*3, c);
    array_int *array = (array_int*) c;
    array->size = 3;
    int *b = (int*) (c+sizeof(array_int));
    b[0] = 123456789;
    b[1] = 234567890;
    b[2] = 345678901;

    array_int* result = read_int_array(&buf);
    ASSERT_EQ(result->size, 3);
    for (int i = 0; i < result->size; ++i) {
        ASSERT_EQ(b[i], result->elements[i]);
    }
}