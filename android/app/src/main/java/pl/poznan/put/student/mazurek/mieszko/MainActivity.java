package pl.poznan.put.student.mazurek.mieszko;

import android.app.Activity;
import android.os.Bundle;

public class MainActivity extends Activity {
    private GameView view;

    @Override
    public void onCreate(Bundle state) {
        super.onCreate(state);

        view = new GameView(this);

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
