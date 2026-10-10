#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_android.h"
#include "StrEnc.h"

#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

JavaVM *jvm;

using json = nlohmann::json;
std::string g_Token, g_Auth;
bool bValid = false;

struct MemoryStruct {
	char *memory;
	size_t size;
};

jobject getGlobalContext(JNIEnv *env)
{
    jclass activityThread = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jmethodID currentActivityThread = env->GetStaticMethodID(activityThread, OBFUSCATE("currentActivityThread"), OBFUSCATE("()Landroid/app/ActivityThread;"));
    jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);
    jmethodID getApplication = env->GetMethodID(activityThread, OBFUSCATE("getApplication"), OBFUSCATE("()Landroid/app/Application;"));
    jobject context = env->CallObjectMethod(at, getApplication);
    return context;
}

void displayKeyboard(bool pShow) {
    JNIEnv *env = getEnv();
    jclass ctx = env->FindClass(OBFUSCATE("android/content/Context"));
    jfieldID fid = env->GetStaticFieldID(ctx, OBFUSCATE("INPUT_METHOD_SERVICE"), OBFUSCATE("Ljava/lang/String;"));
    jmethodID mid = env->GetMethodID(ctx, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
    jobject context = env->GetStaticObjectField(UnityPlayer_cls, UnityPlayer_CurrentActivity_fid);
    jobject InputManObj = env->CallObjectMethod(context, mid, (jstring) env->GetStaticObjectField(ctx, fid));
    jclass ClassInputMethodManager = env->FindClass(OBFUSCATE("android/view/inputmethod/InputMethodManager"));
    jmethodID toggleSoftInputId = env->GetMethodID(ClassInputMethodManager, OBFUSCATE("toggleSoftInput"), OBFUSCATE("(II)V"));
    if (pShow) {
        env->CallVoidMethod(InputManObj, toggleSoftInputId, 2, 0);
    } else {
        env->CallVoidMethod(InputManObj, toggleSoftInputId, 0, 0);
    }
}



static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *) userp;
	
	mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		return 0;
	}
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return realsize;
}
int ShowSoftKeyboardInput()
{
    

    jint jni_return = jvm->GetEnv((void**)&java_env, JNI_VERSION_1_6);
    if (jni_return == JNI_ERR)
        return -1;

    jni_return = jvm->AttachCurrentThread(&java_env, NULL);
    if (jni_return != JNI_OK)
        return -2;

    jclass native_activity_clazz = genv->GetObjectClass(g_App->activity->clazz);
    if (native_activity_clazz == NULL)
        return -3;

    jmethodID method_id = genv->GetMethodID(native_activity_clazz, "showSoftInput", "()V");
    if (method_id == NULL)
        return -4;

    genv->CallVoidMethod(g_App->activity->clazz, method_id);

    jni_return = jvm->DetachCurrentThread();
    if (jni_return != JNI_OK)
        return -5;

    return 0;
}
int PollUnicodeChars() {
	JNIEnv *env;
	jvm->AttachCurrentThread(&env, NULL);
	
	jclass looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
	auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
	env->CallStaticVoidMethod(looperClass, prepareMethod);
	
	jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
	jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
	
	jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
	jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
	
	jclass keyEventClass = env->FindClass(OBFUSCATE("android/view/KeyEvent"));
	jmethodID getUnicodeCharMethod = env->GetMethodID(keyEventClass, OBFUSCATE("getUnicodeChar"), OBFUSCATE("(I)I"));
	
	ImGuiIO& io = ImGui::GetIO();
    
	int return_key = env->CallIntMethod(keyEventClass, getUnicodeCharMethod);
	
	env->DeleteLocalRef(keyEventClass);
	env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass);
	jvm->DetachCurrentThread();
	
	return return_key;
}
