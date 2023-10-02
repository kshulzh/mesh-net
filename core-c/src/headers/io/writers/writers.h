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

#ifndef MESH_NET_WRITERS_H
#define MESH_NET_WRITERS_H

#include "../buffer.h"

#define WRITE_TEMPLATE(TYPE) \
TYPE *write_##TYPE(buffer *buf, TYPE *data); \

#define WRITE_ARRAY_TEMPLATE(TYPE) \
array_##TYPE *write_##TYPE##_array(buffer *buf, array_##TYPE *array);

#define WRITE_BOTH_TEMPLATES(TYPE) \
WRITE_TEMPLATE(TYPE)              \
WRITE_ARRAY_TEMPLATE(TYPE)

WRITE_BOTH_TEMPLATES(char)

WRITE_BOTH_TEMPLATES(short)

WRITE_BOTH_TEMPLATES(int)

WRITE_BOTH_TEMPLATES(long)

void encode_char_array(buffer *b, array_char *);

#endif //MESH_NET_WRITERS_H
