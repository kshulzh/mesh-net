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

#ifndef MESH_NET_MAP_H
#define MESH_NET_MAP_H

#include "array.h"
#include "pair.h"

#define MAP(KEY, VALUE) \
PAIR(KEY,VALUE)\
ARRAY_DECLARATION(pair_##KEY##_##VALUE) \
struct map_##KEY##_##VALUE {\
    array_pair_##KEY##_##VALUE elements; \
};\
typedef struct map_##KEY##_##VALUE map_##KEY##_##VALUE;
MAP(int, int)
#endif //MESH_NET_MAP_H
