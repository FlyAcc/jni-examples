#include <jni.h>
#include <stdio.h>

JNIEXPORT jstring JNICALL
Java_ConstructorCall_newString(JNIEnv *env, jobject obj, jstring str, jint len)
{
    jclass stringClass;
    jmethodID cid;
    jcharArray elemArr;
    jstring result;
    stringClass = (*env)->FindClass(env, "java/lang/String");
    if (stringClass == NULL)
    {
        return NULL; /* exception thrown */
    }
    /* Get the method ID for the String(char[]) constructor */
    cid = (*env)->GetMethodID(env, stringClass,
                              "<init>", "([C)V");
    if (cid == NULL)
    {
        return NULL; /* exception thrown */
    }
    /* Create a char[] that holds the string characters */
    elemArr = (*env)->NewCharArray(env, len);
    if (elemArr == NULL)
    {
        return NULL; /* exception thrown */
    }
    const jchar *chars = (*env)->GetStringChars(env, str, NULL);
    (*env)->SetCharArrayRegion(env, elemArr, 0, len, chars);
    /* Construct a java.lang.String object */
    result = (*env)->NewObject(env, stringClass, cid, elemArr);

    // // 可替代上面的写法，但是更容易出错
    // result = (*env)->AllocObject(env, stringClass);
    // if (result)
    // {
    //     // 注意构造器方法只能调用一次，AllocObject创建了未初始化的对象，每个对象只能初始化一次
    //     (*env)->CallNonvirtualVoidMethod(env, result, stringClass,
    //                                      cid, elemArr); 
    //     /* we need to check for possible exceptions */
    //     if ((*env)->ExceptionCheck(env))
    //     {
    //         (*env)->DeleteLocalRef(env, result);
    //         result = NULL;
    //     }
    // }

    /* Free local references */
    (*env)->DeleteLocalRef(env, elemArr);
    (*env)->DeleteLocalRef(env, stringClass);
    (*env)->ReleaseStringChars(env, str, chars);
    return result;
}