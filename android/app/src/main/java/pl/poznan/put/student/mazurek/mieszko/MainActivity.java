package pl.poznan.put.student.mazurek.mieszko;

import android.app.Activity;
import android.os.Bundle;
import android.view.WindowManager;

public class MainActivity extends Activity {
    private GameView view;

    @Override
    public void onCreate(Bundle state) {
        super.onCreate(state);

        view = new GameView(this);

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        setContentView(view);
    }

    @Override
    protected void onStart() {
        view.start();

        super.onStart();
    }

    @Override
    protected void onStop() {
        super.onStop();

        view.stop();
    }
}
