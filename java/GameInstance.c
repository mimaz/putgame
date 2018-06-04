/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <jni.h>
#include <stdlib.h>

#include <putgame/putgame.h>

#define HANDLE_NAME "handle"
#define HANDLE_SIGN "J"
#define TIMEMS_NAME "timeMillis"
#define TIMEMS_SIGN "()J"

struct internal
{
    struct putgame p;

    JNIEnv *env;
    jobject obj;
};

static time_t get_time_ms(struct putgame *self)
{
    JNIEnv *env = ((struct internal *) self)->env;
    jobject obj = ((struct internal *) self)->obj;

    jclass cls = (*env)->GetObjectClass(env, obj);
    jmethodID id = (*env)->GetMethodID(env, obj, TIMEMS_NAME, TIMEMS_SIGN);

    return (*env)->CallLongMethod(env, obj, id);
}

static struct putgame *get_self(JNIEnv *env, jobject obj)
{
    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID id = (*env)->GetFieldID(env, cls, HANDLE_NAME, HANDLE_SIGN);
    jlong handle = (*env)->GetLongField(env, obj, id);

    struct internal *self = (struct internal *) handle;

    self->env = env;
    self->obj = obj;

    return (struct putgame *) self;
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_start(
        JNIEnv *env,
        jobject obj)
{
    putgame_start(get_self(env, obj));
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_stop(
        JNIEnv *env,
        jobject obj)
{
    putgame_stop(get_self(env, obj));
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_draw(
        JNIEnv *env,
        jobject obj)
{
    putgame_draw(get_self(env, obj));
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_process(
        JNIEnv *env,
        jobject obj)
{
    putgame_process(get_self(env, obj));
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_resize(
        JNIEnv *env,
        jobject obj,
        jint width,
        jint height)
{
    putgame_resize(get_self(env, obj), width, height);
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_cursor(
        JNIEnv *env,
        jobject obj,
        jint x,
        jint y)
{
    putgame_cursor(get_self(env, obj), x, y);
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_press(
        JNIEnv *env,
        jobject obj)
{
    putgame_press(get_self(env, obj));
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_release(
        JNIEnv *env,
        jobject obj)
{
    putgame_release(get_self(env, obj));
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_set(
        JNIEnv *env,
        jobject obj,
        jstring key,
        jstring value)
{
    const char *ckey = (*env)->GetStringUTFChars(env, key, NULL);
    const char *cvalue = (*env)->GetStringUTFChars(env, value, NULL);

    putgame_set(get_self(env, obj), ckey, cvalue);

    (*env)->ReleaseStringUTFChars(env, key, ckey);
    (*env)->ReleaseStringUTFChars(env, value, cvalue);
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_create(
        JNIEnv *env,
        jobject obj)
{
    struct internal *self = malloc(sizeof(struct internal));

    putgame_create((struct putgame *) self, get_time_ms);


    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID id = (*env)->GetFieldID(env, cls, HANDLE_NAME, HANDLE_SIGN);

    jlong handle = (jlong) self;

    (*env)->SetLongField(env, obj, id, handle);
}

JNIEXPORT void JNICALL
Java_pl_poznan_put_student_mazurek_mieszko_GameInstance_destroy(
        JNIEnv *env,
        jobject obj)
{
    struct putgame *self = get_self(env, obj);

    putgame_destroy(self);

    free(self);
}
