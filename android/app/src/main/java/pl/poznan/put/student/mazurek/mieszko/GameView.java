package pl.poznan.put.student.mazurek.mieszko;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameView extends GLSurfaceView {
    private boolean started;
    private boolean stopped;

    private final Renderer renderer;

    public GameView(Context context) {
        super(context);

        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        setEGLContextClientVersion(3);

        started = false;
        stopped = false;

        renderer = new Renderer();
        renderer.set("bottom_offset", "10");

        setRenderer(renderer);
        setOnTouchListener(new TouchListener());
    }

    public void start() {
        started = true;

        int bottomoff = ((MainActivity) getContext()).getNavBarHeight();

        renderer.set("bottom_offset", String.valueOf(bottomoff));
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
            Log.d("TAG", "resize: " + width + " " + height);
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

            nextTime += 1000 / 40;

            process();
            draw();
        }
    }

    private class TouchListener implements OnTouchListener {
        private int last_x;
        private int last_y;

        @Override
        public boolean onTouch(View view, MotionEvent event) {
            int x = (int) event.getX();
            int y = getHeight() - (int) event.getY();

            if (x != last_x || y != last_y) {
                last_x = x;
                last_y = y;

                renderer.cursor(x, y);
            }

            switch (event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    renderer.press();
                    break;

                case MotionEvent.ACTION_UP:
                    renderer.release();
                    break;
            }

            return true;
        }
    }
}
