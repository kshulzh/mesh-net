//
// Created by Kyrylo_Shulzhenko on 10/4/2023.
//

#include <malloc.h>
#include "out.h"
#include "../jvm/jvm.h"

void print(const char *str) {
    JNIEnv *env = n_env();
    jclass syscls = (*env)->FindClass(env,"java/lang/System");
    jfieldID fid = (*env)->GetStaticFieldID(env,syscls, "out", "Ljava/io/PrintStream;");
    jobject out = (*env)->GetStaticObjectField(env,syscls, fid);
    jclass pscls = (*env)->FindClass(env,"java/io/PrintStream");
    jmethodID mid = (*env)->GetMethodID(env,pscls, "println", "(Ljava/lang/String;)V");
    jstring str1 = (*env)->NewStringUTF(env,str);
    (*env)->CallVoidMethod(env,out, mid, str1);
    //(*env)->DeleteGlobalRef(env,str1);
}
