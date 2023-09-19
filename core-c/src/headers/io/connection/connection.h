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

#ifndef MESH_NET_CONNECTION_H
#define MESH_NET_CONNECTION_H

typedef struct {
    void (*open)(void *thiz);

    void (*close)(void *thiz);

    bool (*is_connected)(void *thiz);

    int (*read)(void *thiz);

    int (*read_array)(void *thiz, char[], int, int);

    void (*write)(void *thiz, int);

    void (*write_array)(void *thiz, char[], int);

    void *(*get_properties)(void *thiz);

    void (*set_properties)(void *thiz, void *);
} connection;
#endif //MESH_NET_CONNECTION_H
