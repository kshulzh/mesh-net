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

#ifndef MESH_NET_CONNECTION_BUFFERED_H
#define MESH_NET_CONNECTION_BUFFERED_H

#include "connection.h"
#include "containers/list.h"
#include "io/buffer.h"

typedef struct {
    connection *c;
    list buffers;

    void (*on_read_handler)(void *thiz, buffer *);
} connection_buffer;

void connection_buffer_read(connection_buffer *thiz);

void default_on_read_handler(void *thiz, buffer *b);

connection_buffer *new_connection_buffer(connection *c);

#endif //MESH_NET_CONNECTION_BUFFERED_H
