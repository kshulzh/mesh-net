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

#ifndef MESH_NET_READERS_H
#define MESH_NET_READERS_H

#include "../buffer.h"

#define READ_TEMPLATE(TYPE) \
TYPE *read_##TYPE(buffer *buf); \

#define READ_ARRAY_TEMPLATE(TYPE) \
array_##TYPE *read_##TYPE##_array(buffer *buf);

#define READ_BOTH_TEMPLATES(TYPE) \
READ_TEMPLATE(TYPE)              \
READ_ARRAY_TEMPLATE(TYPE)

READ_BOTH_TEMPLATES(char)
READ_BOTH_TEMPLATES(short)
READ_BOTH_TEMPLATES(int)
READ_BOTH_TEMPLATES(long)


#endif //MESH_NET_READERS_H
