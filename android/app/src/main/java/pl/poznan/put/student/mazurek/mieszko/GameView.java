package pl.poznan.put.student.mazurek.mieszko;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameView extends GLSurfaceView {
    private Renderer renderer;
    private boolean started;
    private boolean stopped;

    public GameView(Context context) {
        super(context);

        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(3);

        renderer = new Renderer();
        started = false;
        stopped = false;

        setRenderer(renderer);
    }

    public void start() {
        started = true;
    }

    public void stop() {
        stopped = true;
    }

    private class Renderer extends GameInstance implements GLSurfaceView.Renderer {
        private long nextTime = timeMillis();

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {}

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            resize(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            if (started) {
                started = false;
                start();
            }

            if (stopped) {
                stopped = false;
                stop();
            }

            while (timeMillis() < nextTime) {
                try {
                    Thread.sleep(nextTime - timeMillis());
                } catch (InterruptedException e) {
                }
            }

            nextTime += 1000 / 30;

            draw();
        }
    }
}
