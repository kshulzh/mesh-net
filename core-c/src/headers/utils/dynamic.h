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

#ifndef MESH_NET_DYNAMIC_H
#define MESH_NET_DYNAMIC_H

#include "../containers/array.h"

typedef enum {
    OBJECT,
    INT8,
    INT16,
    INT32,
    INT64,
    FLOAT,
    DOUBLE,
    ARRAY_OBJECT,
    ARRAY_INT8,
    ARRAY_INT16,
    ARRAY_INT32,
    ARRAY_INT64,
    ARRAY_FLOAT,
    ARRAY_DOUBLE,
} types;

typedef struct {
    types type;
    union {
        uint8_t uint8;
        uint16_t uint16;
        uint32_t uint32;
        uint64_t uint64;
        int8_t int8;
        int16_t int16;
        int32_t int32;
        int64_t int64;
        float _float;
        double _double;
        void* object;
        ARRAY(uint8_t)* array_uint8;
        ARRAY(uint16_t)* array_uint16;
        ARRAY(uint32_t)* array_uint32;
        ARRAY(uint64_t)* array_uint64;
        ARRAY(int8_t)* array_int8;
        ARRAY(int16_t)* array_int16;
        ARRAY(int32_t)* array_int32;
        ARRAY(int64_t)* array_int64;
        ARRAY(float)* array_float;
        ARRAY(double)* array_double;
        ARRAY(void*)* array_objects;
    } value;
} dynamic;


#endif //MESH_NET_DYNAMIC_H
