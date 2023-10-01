//
// Created by kirill on 30.09.23.
//

#ifndef MESH_NET_BUFFER_UTILS_H
#define MESH_NET_BUFFER_UTILS_H


#include "containers/list.h"

list * create_buffers(int count, int size);

buffer *create_buffer(int size);
#endif //MESH_NET_BUFFER_UTILS_H
