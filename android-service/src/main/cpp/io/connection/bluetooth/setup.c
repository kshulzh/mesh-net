#include <jni.h>
#include "../../../conf/inst.h"
#include "bluetooth_radar.h"
#include "../../../log/out.h"
#include "io/connection/connection.h"
#include "services/connection/functions.h"
#include "io/connection/connection_buffered.h"

//
// Created by Kyrylo_Shulzhenko on 10/4/2023.
//
void on_find_handler(void *thiz,void *c) {
    radar *r = thiz;
    instance *inst = r->inst;
    connection *con = c;
    con->open(con);
    list_add(&inst->connections,c);
    list_add(&inst->buffered_connections,new_connection_buffer(c));

    print("found device");
}


JNIEXPORT jlong JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_bluetooth_BlueToothCKt_setup1(JNIEnv *env,
                                                                             jclass clazz,
                                                                             jobject btr) {
    instance *inst = get_inst();
    bluetooth_radar *br = new_bluetooth_radar();
    br->btr = (*env)->NewGlobalRef(env,btr);
    br->on_find_device_handler = on_find_handler;
    if(inst == 0) {
        print("inst is null\n");
    }
    instance_add_radar(inst,br);
    return (long ) br;
}