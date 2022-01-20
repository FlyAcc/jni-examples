#include <jni.h>
#include <stdio.h>
#include "Child.h"

JNIEXPORT void JNICALL
Java_Child_nativeMethod(JNIEnv *env, jobject obj)
{
    jclass cls = (*env)->GetObjectClass(env, obj);
    jclass scls = (*env)->FindClass(env, "Parent");
    jmethodID mid = (*env)->GetMethodID(env, cls, "callback", "()V");
    jmethodID smid = (*env)->GetMethodID(env, scls, "callback", "()V");
    if (mid == NULL)
    {
        return;
    }

    printf("In C\n");

    (*env)->CallVoidMethod(env, obj, mid);
    (*env)->CallNonvirtualVoidMethod(env, obj, scls, smid);
}