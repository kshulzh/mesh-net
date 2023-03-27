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
#include "io/writers/writers.h"
#include "io/readers/readers.h"

TEST(writer, write_int) {
    int expected = 1234567;
    auto * stream = new std::stringstream();

    write(stream,&expected);
    ASSERT_EQ(expected, *read<int>(stream));
}

TEST(writer, write_string) {
    auto expected = "hello";
    auto * stream = new std::stringstream();

    write_array(stream,expected,5);
    auto* result = read_array<char>(stream);
    ASSERT_EQ(5, result->size);
    for(int i=0;i<5;i++){
        ASSERT_EQ(expected[i], result->v[i]);
    }
}