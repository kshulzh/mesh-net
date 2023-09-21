//
// Created by kirill on 18.09.23.
//

#ifndef MESH_NET_MOCK_CONNECTION_H
#define MESH_NET_MOCK_CONNECTION_H

#include "containers/list.h"
#include "io/connection/connection.h"
#include "io/buffer.h"
#include "utils/new.h"
#include "io/readers/readers.h"
#include "utils/math.h"

typedef struct {
    connection c;
    buffer *b;
    void * paired;
    char is_opened;
    char is_ready;
} mock_connection;
void mock_connection_open(void *thiz) {
    mock_connection* mc = (mock_connection *) thiz;
    mc->is_opened = true;
}

void mock_connection_close(void *thiz) {
    mock_connection* mc = (mock_connection *) thiz;
    mc->is_opened = false;

}

char mock_connection_is_connected(void *thiz) {
    mock_connection* mc = (mock_connection *) thiz;
    return mc->is_opened;
}

int mock_connection_read(void *thiz) {
    mock_connection* mc = (mock_connection *) thiz;
    if (mc->is_opened == 0) {
        return -1;
    }
    return *read_char(mc->b);

}

int mock_connection_read_array(void *thiz, char* array, int size, int offset) {
    mock_connection* mc = (mock_connection *) thiz;
    if (mc->is_opened == 0) {
        return -1;
    }
    int s = min(size,mc->b->temp-mc->b->start);
    mem_copy(array, mc->b->start, s);
    return s;
}

void mock_connection_write(void *thiz, int b) {
    mock_connection* mc = (mock_connection *) thiz;
    if (mc->is_opened == 0) {
        return;
    }
    mock_connection* mc_other = (mock_connection *) mc->paired;
    write_to_buffer(mc_other->b,&b,1);
    mc_other->is_ready = true;
}

void mock_connection_write_array(void *thiz, char* data, int size) {
    mock_connection* mc = (mock_connection *) thiz;
    if (mc->is_opened == 0) {
        return;
    }
    mock_connection* mc_other = (mock_connection *) mc->paired;
    write_to_buffer(mc_other->b,data,size);
    mc_other->is_ready = true;
}

void *mock_connection_get_properties(void *thiz) {
    mock_connection* mc = (mock_connection *) thiz;
    return 0;
}

void mock_connection_set_properties(void *thiz, void *);
mock_connection* new_mock_connection(buffer *b) {
    mock_connection* mc = New(mock_connection);
    mc->b = b;

    mc->c.open = mock_connection_open;
    mc->c.close = mock_connection_close;
    mc->c.is_connected = mock_connection_is_connected;

    mc->c.set_properties = mock_connection_set_properties;
    mc->c.get_properties = mock_connection_get_properties;

    mc->c.read = mock_connection_read;
    mc->c.read_array = mock_connection_read_array;

    mc->c.write = mock_connection_write;
    mc->c.write_array = mock_connection_write_array;

    return mc;
}

mock_connection* new_mock_connection1(int size) {
    char *b1 = (char*) malloc(size* sizeof(char));
    buffer *buf1 = New(buffer);
    buffer_init(buf1, size, b1);
    return new_mock_connection(buf1);
}

void mock_connection_link(mock_connection* c1,mock_connection*c2) {
    c1->paired = c2;
    c2->paired = c1;
}

#endif //MESH_NET_MOCK_CONNECTION_H
