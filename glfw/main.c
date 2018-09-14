/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include <putgame/putgame.h>

extern void usleep(time_t);

static struct putgame *instance;
static GLFWwindow *window;

static time_t get_time_ms(struct putgame *self)
{
    (void) self;

    return (time_t)(glfwGetTime() * 1000);
}

static void exit_window(struct putgame *self)
{
    (void) self;

    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void destroy_instance(void)
{
    if (instance != NULL)
    {
        putgame_destruct(instance);

        free(instance);

        instance = NULL;
    }
}

static void create_instance(void)
{
    destroy_instance();

    instance = malloc(sizeof(struct putgame));

    putgame_construct(instance);

    instance->time = get_time_ms;
    instance->exit = exit_window;
}

static void destroy_window(void)
{
    if (window != NULL)
    {
        glfwDestroyWindow(window);
        window = NULL;
    }
}

static void exit_with_error(const char *err)
{
    fprintf(stderr, "%s\n", err);

    destroy_instance();
    destroy_window();

    glfwTerminate();
    exit(1);
}

static void error_callback(int code, const char *desc)
{
    exit_with_error(desc);
}

static void key_callback(GLFWwindow *win,
                         int key, int code,
                         int action, int mode)
{
    (void) win;
    (void) code;
    (void) action;
    (void) mode;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
    }
}

static void resize_callback(GLFWwindow *win,
                            int width, int height)
{
    (void) win;

    putgame_resize(instance, width, height);
}

static void cursor_callback(GLFWwindow *win,
                            double cursorx, 
                            double cursory)
{
    int height;

    glfwGetWindowSize(win, NULL, &height);

    cursory = height - cursory;

    putgame_cursor(instance, (int) cursorx, (int) cursory);
}

static void touch_callback(GLFWwindow *win,
                           int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        switch (action)
        {
        case GLFW_PRESS:
            putgame_press(instance);
            break;

        case GLFW_RELEASE:
            putgame_release(instance);
            break;
        }
    }
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    if (! glfwInit())
        exit_with_error("initialization GLFW failed!");


    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, 
                   GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(960, 540, 
                              "putgame", 
                              NULL,
                              //glfwGetPrimaryMonitor(),
                              NULL);

    if (window == NULL)
        exit_with_error("creating GLFW window failed");

    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, resize_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, touch_callback);
    glfwMakeContextCurrent(window);


    create_instance();

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    putgame_start(instance);
    putgame_resize(instance, width, height);

    double nexttim = glfwGetTime();


    putgame_set(instance, "bottom_offset", "0");


    while (! glfwWindowShouldClose(window))
    {
        glfwPollEvents();


        putgame_draw(instance);


        glfwSwapBuffers(window);
        

        nexttim += 1.0 / FPS;

        while (glfwGetTime() < nexttim)
            usleep(1000);
    }

    putgame_stop(instance);



    destroy_instance();
    destroy_window();

    glfwTerminate();

    return 0;
}
