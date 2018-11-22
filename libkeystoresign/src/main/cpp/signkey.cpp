#include <jni.h>  
#include<android/log.h>  
#include <string.h>  
#include <unistd.h>  
  
extern "C" {

static jstring signData(JNIEnv *env, jclass jcl,
                        jobject context_object) {
    jclass context_class = env->GetObjectClass(context_object);

    //context.getPackageManager()
    jmethodID methodId = env->GetMethodID(context_class, "getPackageManager",
                                          "()Landroid/content/pm/PackageManager;");
    jobject package_manager_object = env->CallObjectMethod(context_object, methodId);
    if (package_manager_object == NULL) {
        __android_log_print(ANDROID_LOG_INFO, "JNITag", "getPackageManager() Failed!");
        return NULL;
    }

    //context.getPackageName()
    methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
    jstring package_name_string = (jstring) env->CallObjectMethod(context_object, methodId);
    if (package_name_string == NULL) {
        __android_log_print(ANDROID_LOG_INFO, "JNITag", "getPackageName() Failed!");
        return NULL;
    }

    env->DeleteLocalRef(context_class);

    //PackageManager.getPackageInfo(Sting, int)
    jclass pack_manager_class = env->GetObjectClass(package_manager_object);
    methodId = env->GetMethodID(pack_manager_class, "getPackageInfo",
                                "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    env->DeleteLocalRef(pack_manager_class);
    jobject package_info_object = env->CallObjectMethod(package_manager_object, methodId,
                                                        package_name_string, 64);
    if (package_info_object == NULL) {
        __android_log_print(ANDROID_LOG_INFO, "JNITag", "getPackageInfo() Failed!");
        return NULL;
    }

    env->DeleteLocalRef(package_manager_object);

    //PackageInfo.signatures[0]
    jclass package_info_class = env->GetObjectClass(package_info_object);
    jfieldID fieldId = env->GetFieldID(package_info_class, "signatures",
                                       "[Landroid/content/pm/Signature;");
    env->DeleteLocalRef(package_info_class);
    jobjectArray signature_object_array = (jobjectArray) env->GetObjectField(package_info_object,
                                                                             fieldId);
    if (signature_object_array == NULL) {
        __android_log_print(ANDROID_LOG_INFO, "JNITag", "PackageInfo.signatures[] is null");
        return NULL;
    }
    jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);

    env->DeleteLocalRef(package_info_object);

    //Signature.toCharsString()
    jclass signature_class = env->GetObjectClass(signature_object);
    methodId = env->GetMethodID(signature_class, "toCharsString", "()Ljava/lang/String;");
    env->DeleteLocalRef(signature_class);
    jstring signature_string = (jstring) env->CallObjectMethod(signature_object, methodId);

    return signature_string;

}
JNIEXPORT jstring JNICALL
Java_io_yylyingy_github_libkeystoresign_Keysignlib_signData(JNIEnv *env, jclass jcl,
                                                            jobject context_object) {
    return signData(env, jcl, context_object);
}

}