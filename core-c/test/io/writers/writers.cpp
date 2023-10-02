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
#include "io/writers/writers.h"
#include "io/buffer.h"
}
TEST(writers, write_char) {
    char b[30];
    buffer buf;
    buffer_init(&buf, 30, b);
    char expected_char = 'c';
    write_char(&buf, &expected_char);
    buffer_init(&buf, 30, b);

    char result_char = *read_char(&buf);
    ASSERT_EQ(expected_char, result_char);
}

TEST(writers, write_int) {
    char b[30];
    buffer buf;
    buffer_init(&buf, 30, b);
    int expected_int = 1234567;
    write_int(&buf, &expected_int);
    buffer_init(&buf, 30, b);

    int result_int = *read_int(&buf);
    ASSERT_EQ(expected_int, result_int);
}

TEST(writers, write_int_array) {
    char b[30];
    int elements[3];
    buffer buf;
    array_int array;
    buffer_init(&buf, 30, b);
    array.size = 3;
    array.elements = elements;
    elements[0] = 123456789;
    elements[1] = 234567890;
    elements[2] = 345678901;

    write_int_array(&buf, &array);
    buffer_init(&buf, 30, b);
    array_int *result = read_int_array(&buf);

    ASSERT_EQ(result->size, 3);
    for (int i = 0; i < result->size; ++i) {
        ASSERT_EQ(elements[i], result->elements[i]);
    }
}