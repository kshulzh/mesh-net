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

#include "io/writers/writers.h"

#define WRITE_TEMPLATE_IMPL(TYPE) \
TYPE* write_##TYPE(buffer *buf, TYPE *data) { \
return (TYPE*) write_to_buffer(buf,data, sizeof(TYPE));\
} \

#define WRITE_ARRAY_TEMPLATE_IMPL(TYPE) \
WRITE_TEMPLATE_IMPL(array_##TYPE)\
array_##TYPE * write_##TYPE##_array(buffer *buf, array_##TYPE *data) {\
    array_##TYPE *array = write_array_##TYPE(buf, data);\
    array->elements = (TYPE*) write_to_buffer(buf,data->elements, sizeof(TYPE)*data->size);\
    return array;\
}

#define WRITE_BOTH_TEMPLATES_IMPL(TYPE) \
WRITE_TEMPLATE_IMPL(TYPE)              \
WRITE_ARRAY_TEMPLATE_IMPL(TYPE)

WRITE_BOTH_TEMPLATES_IMPL(char)
WRITE_BOTH_TEMPLATES_IMPL(short)
WRITE_BOTH_TEMPLATES_IMPL(int)
WRITE_BOTH_TEMPLATES_IMPL(long)
