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


#ifndef MESH_NET_MOCK_CONNECTION_H
#define MESH_NET_MOCK_CONNECTION_H

#include "io/connection/connection.h"
#include "io/buffer.h"
typedef struct {
    connection c;
    list *buffers;
    void * paired;
    char is_opened;
    char is_ready;
} mock_connection;
void mock_connection_open(void *thiz);

void mock_connection_close(void *thiz);

char mock_connection_is_connected(void *thiz);

int32_t  mock_connection_read_array(void *thiz, uint8_t * array, uint32_t size, uint32_t offset);

int32_t mock_connection_write_array(void *thiz, uint8_t * data, uint32_t size);

void *mock_connection_get_properties(void *thiz);

void mock_connection_set_properties(void *thiz, void *);
mock_connection* new_mock_connection(list *buffers) ;

mock_connection* new_mock_connection1(int size) ;

void mock_connection_link(mock_connection* c1,mock_connection*c2);


#endif //MESH_NET_MOCK_CONNECTION_H
