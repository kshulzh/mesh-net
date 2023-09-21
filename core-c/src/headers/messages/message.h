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

#ifndef MESH_NET_MESSAGE_H
#define MESH_NET_MESSAGE_H

#include "io/connection/connection.h"
#include "io/buffer.h"

enum message_type {
    CONNECTION,
    SPREAD,
    ROUTE
};

typedef struct {
    short size;
    enum message_type type;
    char *bytes;
    connection *c;
} message;

message* message_of_buffer(buffer* b) {
    message *m = New(message);
    m->bytes = b->start;
    m->size = b->end - b->start;
    return m;
}

#endif //MESH_NET_MESSAGE_H
