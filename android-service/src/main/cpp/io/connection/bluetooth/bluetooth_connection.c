//
// Created by Kyrylo_Shulzhenko on 10/3/2023.
//

#include "bluetooth_connection.h"
#include "bluetooth_radar.h"
#include "../../../jvm/jvm.h"
#include "../../../log/out.h"

void bluetooth_connection_open(void *thiz) {
    bluetooth_connection *bc = (bluetooth_connection *) thiz;
    JNIEnv *env = n_env();
    jclass clazz = (*(env))->GetObjectClass(env, bc->bluetooth);
    jmethodID open = (*(env))->GetMethodID(env, clazz, "open", "()V");
    (*env)->CallVoidMethod(env, bc->bluetooth, open);
}

void bluetooth_connection_close(void *thiz) {
    bluetooth_connection *bc = (bluetooth_connection *) thiz;
    JNIEnv *env = n_env();
    jclass clazz = (*(env))->GetObjectClass(env, bc->bluetooth);
    jmethodID close = (*(env))->GetMethodID(env, clazz, "close", "()V");
    (*env)->CallVoidMethod(env, bc->bluetooth, close);
}

char bluetooth_connection_is_connected(void *thiz) {
    bluetooth_connection *bc = (bluetooth_connection *) thiz;
    JNIEnv *env = n_env();
    jclass clazz = (*(env))->GetObjectClass(env, bc->bluetooth);
    jmethodID close = (*(env))->GetMethodID(env, clazz, "isConnected", "()Z");
    return (*env)->CallBooleanMethod(env, bc->bluetooth, close);
}

int bluetooth_connection_read(void *thiz) {
    bluetooth_connection *bc = (bluetooth_connection *) thiz;
}

int bluetooth_connection_read_array(void *thiz, char *array, int size, int offset) {
    bluetooth_connection *bc = (bluetooth_connection *) thiz;
    JNIEnv *env = n_env();
    jbyteArray byteArray = (*env)->NewByteArray(env, size);

    jclass clazz = (*(env))->GetObjectClass(env, bc->bluetooth);
    jmethodID read = (*(env))->GetMethodID(env, clazz, "read", "([BI)I");
    int count = (*env)->CallIntMethod(env, bc->bluetooth, read, byteArray, size);

    (*env)->GetByteArrayRegion(env, byteArray, 0, size, array);
    (*env)->DeleteLocalRef(env, byteArray);
    (*env)->DeleteLocalRef(env, clazz);
    return count;
}

void bluetooth_connection_write(void *thiz, int b) {
    bluetooth_connection *bc = (bluetooth_connection *) thiz;
}

void bluetooth_connection_write_array(void *thiz, char *data, int size) {
    bluetooth_connection *bc = (bluetooth_connection *) thiz;
    JNIEnv *env = n_env();
    jbyteArray byteArray = (*env)->NewByteArray(env, size);
    (*env)->SetByteArrayRegion(env, byteArray, 0, size, data);

    jclass clazz = (*(env))->GetObjectClass(env, bc->bluetooth);
    jmethodID write = (*(env))->GetMethodID(env, clazz, "write", "([BI)V");
    (*env)->CallVoidMethod(env, bc->bluetooth, write, byteArray, size);
    (*env)->DeleteLocalRef(env, byteArray);
    (*env)->DeleteLocalRef(env, clazz);
    print("done");
}

void *bluetooth_connection_get_properties(void *thiz) {
    bluetooth_connection *bc = (bluetooth_connection *) thiz;
}

void bluetooth_connection_set_properties(void *thiz, void *) {
    bluetooth_connection *bc = (bluetooth_connection *) thiz;
}

bluetooth_connection *new_bluetooth_connection() {
    bluetooth_connection *bc = New(bluetooth_connection);
    bc->c.open = bluetooth_connection_open;
    bc->c.close = bluetooth_connection_close;
    bc->c.is_connected = bluetooth_connection_is_connected;

    bc->c.read = bluetooth_connection_read;
    bc->c.read_array = bluetooth_connection_read_array;

    bc->c.write = bluetooth_connection_write;
    bc->c.write_array = bluetooth_connection_write_array;

    bc->c.set_properties = bluetooth_connection_set_properties;
    bc->c.get_properties = bluetooth_connection_get_properties;

    return bc;
}

JNIEXPORT jlong JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_bluetooth_BlueToothCKt_addToRadar(JNIEnv *env,
                                                                                 jclass clazz,
                                                                                 jlong radar_ptr,
                                                                                 jobject bt
) {
    bluetooth_radar *br = (bluetooth_radar *) radar_ptr;
    bluetooth_connection *bc = new_bluetooth_connection();
    bc->c.r = br;
    bc->bluetooth = (*env)->NewGlobalRef(env, bt);
    list_add(&br->connections, bc);

    return (long) bc;

}