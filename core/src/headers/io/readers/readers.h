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

#ifndef MESH_NET_CORE_READERS_H
#define MESH_NET_CORE_READERS_H

#include <istream>
#include "messages/Message.h"

template<typename T>
struct array {
    T *v;
    uint32_t size;

    array(T *v, uint32_t size) : v(v), size(size) {

    }
};

template<typename T>
void read(std::istream *source, T *v) {
    source->read((char *) v, sizeof(T));
}

template<typename T>
T *read(std::istream *source) {
    T *v = new T();
    read(source, v);
    return v;
}

template<typename T>
array<T> *read_array(std::istream *source) {
    uint32_t size = *(read<int>(source));
    T *v = new T[size];
    source->read((char *) v, size * sizeof(T));

    return new array<T>(v,size);
}

#endif //MESH_NET_CORE_READERS_H
