#include <jni.h>
#include "../../../conf/inst.h"
#include "bluetooth_radar.h"
#include "../../../log/out.h"
#include "io/connection/connection.h"
#include "services/connection/functions.h"
#include "io/connection/connection_buffered.h"
#include "services/route/messages.h"
#include "../../../jvm/jvm.h"
#include "services/route/handlers.h"

//
// Created by Kyrylo_Shulzhenko on 10/4/2023.
//

jobject localVpn = 0;

void on_find_handler(void *thiz, void *c) {
    radar *r = thiz;
    instance *inst = r->inst;
    connection *con = c;
    con->open(con);
    list_add(&inst->connections, c);
    list_add(&inst->buffered_connections, new_connection_buffer(c));

    print("found device");
}

static void handle_udp_msg(route_udp_message *rum) {
    JNIEnv *env = n_env();
    jbyteArray byteArray = (*env)->NewByteArray(env, rum->msg->size);

    (*env)->SetByteArrayRegion(env, byteArray, 0, rum->msg->size, rum->msg->elements);

    jclass clazz = (*(env))->GetObjectClass(env, localVpn);
    jmethodID write = (*(env))->GetMethodID(env, clazz, "write", "([BJ)V");
    (*env)->CallVoidMethod(env, localVpn, write, byteArray,
                           (jlong) (((long) list_get_by_id(rum->way, 0))));
    (*env)->DeleteLocalRef(env, byteArray);
}


JNIEXPORT jlong JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_bluetooth_BlueToothCKt_setup1(JNIEnv *env,
                                                                             jclass clazz,
                                                                             jobject btr) {
    instance *inst = get_inst();
    bluetooth_radar *br = new_bluetooth_radar();
    br->btr = (*env)->NewGlobalRef(env, btr);
    print("new radar");
    br->r.on_find_device_handler = on_find_handler;
    if (inst == 0) {
        print("inst is null\n");
    }
    instance_add_radar(inst, br);
    return (long) br;
}

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_vpn_LocalVpnService_registerUdpCallBack(JNIEnv *env,
                                                                                  jobject thiz) {
    if (localVpn != 0) {
        (*env)->DeleteGlobalRef(env, localVpn);
    }
    localVpn = (*env)->NewGlobalRef(env, thiz);
    udp_handler1()[0] = handle_udp_msg;
}