#include <jni.h>
#include "services/connection/functions.h"
#include "services/route/functions.h"
#include "inst.h"

//
// Created by Kyrylo_Shulzhenko on 10/5/2023.
//

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_ExportKt_connectionAsk(JNIEnv *env, jclass clazz,
                                                                      jlong ptr) {
    connection_ask((void*) ptr);
}

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_ExportKt_connectionGetStruct(JNIEnv *env,
                                                                            jclass clazz,
                                                                            jlong ptr) {
    connection_get_struct((void*) ptr);
}

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_ExportKt_routeUdp(JNIEnv *env, jclass clazz,
                                                                 jlong id, jbyteArray byte_array,
                                                                 jint size) {
    route_udp(get_inst(),id,byte_array,size);
}