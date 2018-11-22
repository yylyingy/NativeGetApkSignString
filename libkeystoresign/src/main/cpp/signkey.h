//
// Created by Yangyl on 2017/4/6.
//

#ifndef TUANDAI_SIGNKEY_H
#define TUANDAI_SIGNKEY_H

#include <jni.h>

JNIEXPORT jstring JNICALL Java_io_yylyingy_github_libkeystoresign_Keysignlib_signData(JNIEnv *env, jclass jcl,
                                                                           jobject context_object);

#endif //TUANDAI_SIGNKEY_H
