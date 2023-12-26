//
// Created by Kyrylo_Shulzhenko on 10/3/2023.
//
#include <jni.h>

#include "bluetooth_radar.h"
#include "../../../jvm/jvm.h"
#include "io/connection/connection.h"

void bluetooth_radar_start(void *thiz) {
    bluetooth_radar *bc = (bluetooth_radar *) thiz;
    JNIEnv *env = n_env();
    jclass clazz = (*(env))->GetObjectClass(env, bc->btr);
    jmethodID start = (*(env))->GetMethodID(env, clazz, "start", "()V");
    (*env)->CallVoidMethod(env, bc->btr, start);
}

void bluetooth_radar_stop(void *thiz) {
    bluetooth_radar *bc = (bluetooth_radar *) thiz;
    JNIEnv *env = n_env();
    jclass clazz = (*(env))->GetObjectClass(env, bc->btr);
    jmethodID stop = (*(env))->GetMethodID(env, clazz, "stop", "()V");
    (*env)->CallVoidMethod(env, bc->btr, stop);
}

char bluetooth_radar_is_started(void *thiz) {
    bluetooth_radar *bc = (bluetooth_radar *) thiz;
    JNIEnv *env = n_env();
    jclass clazz = (*(env))->GetObjectClass(env, bc->btr);
    jmethodID is_discovering = (*(env))->GetMethodID(env, clazz, "isDiscovering", "()Z");
    (*env)->CallBooleanMethod(env, bc->btr, is_discovering);
    (*env)->DeleteLocalRef(env, clazz);
    return 1;//(char) ((*env)->CallBooleanMethod(env,br->adapter,start_discovery));
}

void bluetooth_radar_scan(void *thiz) {
    bluetooth_radar *br = (bluetooth_radar *) thiz;
    if (br->connections.size > 0) {
        connection *c = list_remove_first(&br->connections);
        br->r.on_find_device_handler(br, c);
    }
}

void bluetooth_radar_set_properties(void *thiz, void *) {
    bluetooth_radar *br = (bluetooth_radar *) thiz;
}

void *bluetooth_radar_get_properties(void *thiz) {
    bluetooth_radar *br = (bluetooth_radar *) thiz;
}

bluetooth_radar *new_bluetooth_radar() {
    bluetooth_radar *br = New(bluetooth_radar);
    br->r.start = bluetooth_radar_start;
    br->r.stop = bluetooth_radar_stop;
    br->r.is_running = bluetooth_radar_is_started;
    br->r.scan = bluetooth_radar_scan;
    br->r.set_properties = bluetooth_radar_set_properties;
    br->r.get_properties = bluetooth_radar_get_properties;
    list_reset(&(br->connections));

    return br;
}
