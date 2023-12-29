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

#ifndef MESH_NET_ARRAY_H
#define MESH_NET_ARRAY_H
#include <stdint.h>
#define ARRAY_DECLARATION(TYPE)\
typedef struct { \
   unsigned int size; \
   TYPE *elements;\
} array_##TYPE;\

#define ARRAY(TYPE) array_##TYPE
ARRAY_DECLARATION(char)
ARRAY_DECLARATION(uint8_t)
ARRAY_DECLARATION(uint16_t)
ARRAY_DECLARATION(uint32_t)
ARRAY_DECLARATION(uint64_t)
ARRAY_DECLARATION(int8_t)
ARRAY_DECLARATION(int16_t)
ARRAY_DECLARATION(int32_t)
ARRAY_DECLARATION(int64_t)
ARRAY_DECLARATION(float)
ARRAY_DECLARATION(double)
ARRAY_DECLARATION(void)

#endif //MESH_NET_ARRAY_H
