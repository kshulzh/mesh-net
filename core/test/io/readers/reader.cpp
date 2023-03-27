/*
 * Copyright (c) 2023 Kirill Shulzhenko
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
#include "io/readers/readers.h"

template<typename T>
std::stringstream * build_stream_from_array(T * values,int size) {
    auto * stream = new std::stringstream();
    for (int i = 0; i < size; ++i) {
        stream->write((char*) (values + i * sizeof(T)), sizeof(T));
    }

    return stream;
}

TEST(reader, read_char) {
    char expected_char = 'c';
    auto *s = build_stream_from_array(&expected_char, 1);

    auto *result = read<char>(s);
    ASSERT_EQ(expected_char, *result);
}

TEST(reader, read_int) {
    int expected_int = 12256;
    auto *s = build_stream_from_array(&expected_int, 1);

    auto *result = read<int>(s);
    ASSERT_EQ(expected_int, *result);
}

TEST(reader, read_chars) {
    char expected[] = {'1', '1'};
    auto *s = build_stream_from_array(expected, 2);

    auto *result = read<short>(s);
    ASSERT_EQ(*((short *) expected), *result);
}

TEST(reader, read_string) {
    char expected[] = {0,0,0,4, '1','4','3','2'};
    auto *s = build_stream_from_array(expected, 8);

    auto *result = read_array<char>(s)->v;
    ASSERT_EQ(*((int *) (expected+4)), *((int*)result));
}