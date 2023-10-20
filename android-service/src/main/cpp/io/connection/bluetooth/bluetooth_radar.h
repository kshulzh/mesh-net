//
// Created by Kyrylo_Shulzhenko on 10/3/2023.
//

#ifndef MESH_NET_BLUETOOTH_RADAR_H
#define MESH_NET_BLUETOOTH_RADAR_H

#include <jni.h>
#include "devices/device.h"
#include "io/connection/radar.h"
#include "containers/list.h"

jobject *bluetooth_adapter();

typedef struct {
    radar r;

    void (*on_find_device_handler)(void *thiz, void *);

    jobject btr;
    list connections;
} bluetooth_radar;

void bluetooth_radar_start(void *thiz);

void bluetooth_radar_stop(void *thiz);

char bluetooth_radar_is_started(void *thiz);

void bluetooth_radar_scan(void *thiz);


void bluetooth_radar_set_properties(void *thiz, void *);


void *bluetooth_radar_get_properties(void *thiz);


void
bluetooth_on_find_device_handler(void *thiz, void (*on_find_device_handler)(void *thiz, void *));

bluetooth_radar *new_bluetooth_radar();

void bluetooth_radar_find(void *thiz);

#endif //MESH_NET_BLUETOOTH_RADAR_H
