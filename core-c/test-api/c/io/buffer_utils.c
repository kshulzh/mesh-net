//
// Created by kirill on 30.09.23.
//
#include <stdio.h>
#include "io/buffer_utils.h"

list * create_buffers(int count, int size) {
    list * bs = new_list();
    for (int i = 0; i < count; ++i) {
        buffer * b = create_buffer(size);
        list_add(bs, b);
    }

    return bs;
}

buffer *create_buffer(int size) {
    char * arr = mem_alloc(size);
    return new_buffer(arr, size);
};
