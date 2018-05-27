/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

package pl.poznan.put.student.mazurek.mieszko;

abstract class GameInstance
{
    static 
    {
        System.loadLibrary("putgame");
    }

    GameInstance()
    {
        create();
    }

    @Override
    void finalize() throws Throwable
    {
        destroy();

        super.finalize();
    }

    abstract void swapBuffers();

    long timeMillis()
    {
        return System.currentTimeMillis();
    }

    native void start();

    native void stop();

    native void draw();

    native void resize(int width, int height);

    native void cursor(int x, int y);

    native void press();

    native void release();

    private native void create();

    private native void destroy();

    private long handle;
}
