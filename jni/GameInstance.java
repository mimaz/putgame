/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

package pl.poznan.put.student.mazurek.mieszko;

class GameInstance
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
    protected void finalize() throws Throwable
    {
        destroy();

        super.finalize();
    }

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