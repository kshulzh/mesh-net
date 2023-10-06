#include <jni.h>
#include <unistd.h>
#include "inst.h"
#include "../log/out.h"
#include "services/message.h"
#include "services/connection/handlers.h"
#include "services/route/handlers.h"

//
// Created by Kyrylo_Shulzhenko on 10/4/2023.
//
instance * inst;
char is_running = 0;
buffer *create_buffer(int size) {
    char * arr = mem_alloc(size);
    return new_buffer(arr, size);
};
list * create_buffers(int count, int size) {
    list * bs = new_list();
    for (int i = 0; i < count; ++i) {
        buffer * b = create_buffer(size);
        list_add(bs, b);
    }

    return bs;
}

instance* get_inst() {
    return inst;
}

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_Instance_start(JNIEnv *env, jclass clazz) {
    print("start");
    is_running = 1;
    while (is_running) {
        sleep(1);
        print("running");
        instance_run(inst);
    }
}

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_Instance_stop(JNIEnv *env, jclass clazz) {
    is_running = 0;
}

JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_Instance_destroy(JNIEnv *env, jclass clazz) {
    // TODO: implement destroy()
}
JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_Instance_init(JNIEnv *env, jclass clazz, jlong id) {
    connection_setup();
    route_setup();
    inst = new_instance(new_device(id,id));
    list *buffers = create_buffers(10,3000);
    inst->buffers.size = buffers->size;
    inst->buffers.first = buffers->first;
    inst->buffers.last = buffers->last;
}


