#include <jni.h>
#include <string>
#include "sys/socket.h"
extern "C" {
#include "io/connection/bluetooth/bluetooth_radar.h"
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_github_kshulzh_mesh_1net_android_core_StartKt_start1(JNIEnv *env, jclass clazz) {
    bluetooth_radar *r = new_bluetooth_radar();
    r->r.start(r);
}