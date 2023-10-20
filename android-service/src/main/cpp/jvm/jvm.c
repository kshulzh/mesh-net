//
// Created by Kyrylo_Shulzhenko on 10/4/2023.
//
#include "jvm.h"

JavaVM *this_vm;

JavaVM *t_jvm() {
    return this_vm;
}

JNIEnv *n_env() {
    JNIEnv *env;       /* pointer to native method interface */
    (*this_vm)->GetEnv(this_vm, &env, JNI_VERSION_1_6);
    return env;
}


jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    this_vm = vm;
    return JNI_VERSION_1_6;
}