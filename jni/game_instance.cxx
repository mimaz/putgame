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

    struct jni_instance : public game::instance
    {
        static jni_instance *get(JNIEnv *env, jobject obj)
        {
            jclass cls = env->GetObjectClass(obj);
            jfieldID id = env->GetFieldID(cls, "handle", "J");
            jlong handle = env->GetLongField(obj, id);

            auto ins = reinterpret_cast<jni_instance *>(handle);

            ins->env = env;
            ins->obj = obj;

            common::logd("get instance: ", ins);

            return ins;
        }

        jni_instance(JNIEnv *env, jobject obj)
            : env(env)
            , obj(obj)
        {
            jclass cls = env->GetObjectClass(obj);
            jfieldID id = env->GetFieldID(cls, 
                                           handle_name, 
                                           handle_signature);

            common::logd("create instance: ", this);

            auto handle = reinterpret_cast<jlong>(this);

            env->SetLongField(obj, id, handle);
        }

        void swap_buffers() final
        {
            // nothing to do, GLSurfaceView swaps just after draw
        }

        time_t time_millis() final
        {
            auto cls = env->GetObjectClass(obj);
            auto id = env->GetMethodID(cls,
                                       "timeMillis",
                                       "()J");

            return env->CallLongMethod(obj, id);
        }

        JNIEnv *env;
        jobject obj;
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
