//
// Created by alvin on 24/10/2026.
//

#include <jni.h>
#include <string>
#include <algorithm>
#include <vector>

extern "C" JNIEXPORT jobject
jobject
Java_com_alviano_arraymathengine_MainActivity_processUser(
        JNIEnv* env,
        jobject /* this */,
        jobject user_obj) {
    jclass user_class = env->GetObjectClass(user_obj);

    jfieldID name_field_id = env->GetFieldID(user_class, "name", "Ljava/lang/String;");
    jfieldID age_field_id = env->GetFieldID(user_class, "age", "I");

    auto j_name = (jstring) env->GetObjectField(user_obj, name_field_id);
    jint age = env->GetIntField(user_obj, age_field_id);

    const char* native_name = env->GetStringUTFChars(j_name, nullptr);
    std::string name_str(native_name);

    std::string greeting_msg = "Halo " + name_str + " , selamat datang di c++!";
    bool is_adult = (age >= 18);

    jclass stats_class = env->FindClass("com/alviano/arraymathengine/UserStats");
    jmethodID constructor_id = env->GetMethodID(stats_class, "<init>", "(Ljava/lang/String;Z)V");
    jstring j_greeting = env->NewStringUTF(greeting_msg.c_str());

    jobject stats_obj = env->NewObject(stats_class, constructor_id, j_greeting, (j_boolean) is_adult);

    return stats_obj;
}

extern "C" JNIEXPORT jbyteArray
jbyteArray
Java_com_alviano_arraymathengine_MainActivity_xorEncryptDecrypt(
        JNIEnv* env,
        jobject /* this */,
        jbyteArray input_bytes,
        jbyte key) {
    jsize length = env->GetArrayLength(input_bytes);
    jbyte* bytes = env->GetByteArrayElements(input_bytes, nullptr);

    if (bytes == nullptr) return nullptr;

    std::vector<jbyte> output_buffer(length);

    for (int i = 0; i < length; i++) output_buffer[i] = bytes[i] ^ key;

    env->ReleaseByteArrayElements(input_bytes, bytes, JNI_ABORT);

    jbyteArray result = env->NewByteArray(length);
    env->SetByteArrayRegion(result, 0, length, output_buffer.data());

    return result;
}

extern "C" JNIEXPORT jstring
jstring
Java_com_alviano_arraymathengine_MainActivity_reverseAndUppercaseString(
        JNIEnv* env,
        jobject /* this */,
        jstring input_string) {
    const char* native_char_array = env->GetStringUTFChars(input_string, nullptr);

    std::string text(native_char_array);

    env->ReleaseStringUTFChars(input_string, native_char_array);

    std::reverse(text.begin(), text.end());
    for (char &c : text) c = std::toupper(c);

    return env->NewStringUTF(text.c_str());
}

extern "C" JNIEXPORT jfloat
jfloat
Java_com_alviano_arraymathengine_MainActivity_calculateAverage(
        JNIEnv* env,
        jobject /* this */,
        jintArray numbers) {
    jint* elements = env->GetIntArrayElements(numbers, nullptr);
    jsize length = env->GetArrayLength(numbers);

    if (length == 0) return 0.0f;

    long sum = 0;
    for (int i = 0; i < length; i++) sum += elements[i];

    env->ReleaseIntArrayElements(numbers, elements, JNI_ABORT);

    return static_cast<jfloat>(sum) / length;
}