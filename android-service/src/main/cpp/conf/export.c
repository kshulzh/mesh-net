

//
// Created by Kyrylo_Shulzhenko on 10/5/2023.
//
#include <jni.h>
#include "inst.h"
#include "model/instance.h"
#include "services/connection/functions.h"
#include "services/route/messages.h"
#include "services/route/functions.h"
#include "services/route/handlers.h"
#include "services/utils.h"
#include "../log/out.h"
#include "io/writers/writers.h"

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_ExportKt_connectionAsk(JNIEnv *env, jclass clazz,
                                                                      jlong ptr) {
    connection_ask((void *) ptr);
}

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_ExportKt_connectionGetStruct(JNIEnv *env,
                                                                            jclass clazz,
                                                                            jlong ptr) {
    connection_get_struct((void *) ptr);
}

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_ExportKt_routeUdp(JNIEnv *env, jclass clazz,
                                                                 jlong id, jbyteArray byte_array,
                                                                 jint size) {
    char is_copy = 0;
    jbyte *array = (*env)->GetByteArrayElements(env, byte_array, &is_copy);
    route_udp(get_inst(), id, array, size);
}