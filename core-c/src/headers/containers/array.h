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

#define ARRAY(TYPE)\
typedef struct { \
   unsigned int size; \
   TYPE *elements;\
} array_##TYPE;\

#define ARRAY_(TYPE, NAME) \
typedef struct { \
   unsigned int size; \
   TYPE *elements;\
} NAME;                   \

ARRAY(char)
#endif //MESH_NET_ARRAY_H
