/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/game>

#include <jni.h>

namespace
{
    constexpr auto handle_name = "handle";
    constexpr auto handle_signature = "J";

    class jni_instance : public game::instance
    {
    public:
        static jni_instance *get(JNIEnv *env, jobject obj)
        {
            jclass cls = env->GetObjectClass(obj);
            jfieldID id = env->GetFieldID(cls, "handle", "J");
            jlong handle = env->GetLongField(obj, id);

            return reinterpret_cast<jni_instance *>(handle);
        }

        jni_instance(JNIEnv *env, jobject obj)
            : env(env)
            , obj(obj) 
        {
            jclass cls = env->GetObjectClass(obj);


            swap_buffers_id = env->GetMethodID(cls, 
                                               "swapBuffers", 
                                               "()V");

            time_millis_id = env->GetMethodID(cls,
                                              "timeMillis",
                                              "()J");

            jfieldID id = env->GetFieldID(cls, 
                                           handle_name, 
                                           handle_signature);


            auto handle = reinterpret_cast<jlong>(this);

            env->SetLongField(obj, id, handle);
        }

        void swap_buffers() final
        {
            env->CallVoidMethod(obj, swap_buffers_id);
        }

        time_t time_millis() final
        {
            return env->CallLongMethod(obj, time_millis_id);
        }

    private:
        JNIEnv *env;
        jobject obj;
        jmethodID swap_buffers_id;
        jmethodID time_millis_id;
    };
}

extern "C"
{
    JNIEXPORT void JNICALL
    Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_start(
            JNIEnv *env,
            jobject obj)
    {
        common::logd("jni start");
        jni_instance::get(env, obj)->start();
    }

    JNIEXPORT void JNICALL
    Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_stop(
            JNIEnv *env,
            jobject obj)
    {
        common::logd("jni stop");
        jni_instance::get(env, obj)->stop();
    }

    JNIEXPORT void JNICALL
    Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_draw(
            JNIEnv *env,
            jobject obj)
    {
        common::logd("jni draw");
        jni_instance::get(env, obj)->draw();
    }

    JNIEXPORT void JNICALL
    Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_resize(
            JNIEnv *env,
            jobject obj,
            jint width,
            jint height)
    {
        common::logd("jni resize ", width, ":", height);
        jni_instance::get(env, obj)->resize(width, height);
    }

    JNIEXPORT void JNICALL
    Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_cursor(
            JNIEnv *env,
            jobject obj,
            jint x,
            jint y)
    {
        common::logd("jni cursor ", x, ":", y);
        jni_instance::get(env, obj)->cursor(x, y);
    }

    JNIEXPORT void JNICALL
    Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_press(
            JNIEnv *env,
            jobject obj)
    {
        common::logd("jni press");
        jni_instance::get(env, obj)->press();
    }

    JNIEXPORT void JNICALL
    Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_release(
            JNIEnv *env,
            jobject obj)
    {
        common::logd("jni release");
        jni_instance::get(env, obj)->release();
    }

    JNIEXPORT void JNICALL
    Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_create(
            JNIEnv *env,
            jobject obj)
    {
        common::logd("jni create");
        new jni_instance(env, obj);
    }

    JNIEXPORT void JNICALL
    Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_destroy(
            JNIEnv *env,
            jobject obj)
    {
        common::logd("jni destroy");
        delete jni_instance::get(env, obj);
    }
}
