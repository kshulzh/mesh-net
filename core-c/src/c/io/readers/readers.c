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
#include "io/readers/readers.h"

#define READ_TEMPLATE_IMPL(TYPE) \
TYPE *read_##TYPE(buffer * buf) { \
return ( TYPE *) read_from_buffer(buf,sizeof(TYPE)); \
} \

#define READ_ARRAY_TEMPLATE_IMPL(TYPE) \
READ_TEMPLATE_IMPL(array_##TYPE)                                       \
array_##TYPE *read_##TYPE##_array(buffer *buf){\
array_##TYPE * result = read_array_##TYPE(buf);\
if(result->elements != 0) {\
result->elements = read_from_buffer(buf, sizeof(TYPE)*result->size);\
}\
return result;\
}
#define READ_BOTH_TEMPLATES_IMPL(TYPE) \
READ_TEMPLATE_IMPL(TYPE)              \
READ_ARRAY_TEMPLATE_IMPL(TYPE)         \

READ_BOTH_TEMPLATES_IMPL(char)
READ_BOTH_TEMPLATES_IMPL(short)
READ_BOTH_TEMPLATES_IMPL(int)
READ_BOTH_TEMPLATES_IMPL(long)

void* decode_char_array(buffer *b) {
    array_char * ac = (array_char *) read_from_buffer(b, sizeof(array_char));
    ac->elements = read_from_buffer(b,ac->size);
    return ac;
}
