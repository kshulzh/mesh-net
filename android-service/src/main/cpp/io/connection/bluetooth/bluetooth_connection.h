//
// Created by Kyrylo_Shulzhenko on 10/3/2023.
//

#ifndef MESH_NET_BLUETOOTH_CONNECTION_H
#define MESH_NET_BLUETOOTH_CONNECTION_H

#include "io/connection/connection.h"
#include "io/buffer.h"
#include <jni.h>

typedef struct {
    connection c;
    jobject bluetooth;
} bluetooth_connection;

void bluetooth_connection_open(void *thiz);

void bluetooth_connection_close(void *thiz);

char bluetooth_connection_is_connected(void *thiz);

int bluetooth_connection_read(void *thiz);

int bluetooth_connection_read_array(void *thiz, char *array, int size, int offset);

void bluetooth_connection_write(void *thiz, int b);

void bluetooth_connection_write_array(void *thiz, char *data, int size);

void *bluetooth_connection_get_properties(void *thiz);

void bluetooth_connection_set_properties(void *thiz, void *);

bluetooth_connection *new_bluetooth_connection();

#endif //MESH_NET_BLUETOOTH_CONNECTION_H
