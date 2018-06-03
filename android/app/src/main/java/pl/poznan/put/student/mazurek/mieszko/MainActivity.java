package pl.poznan.put.student.mazurek.mieszko;

import android.app.Activity;
import android.os.Bundle;
import android.view.WindowManager;
import android.content.Context;
import android.view.ViewConfiguration;
import android.view.KeyCharacterMap;
import android.view.KeyEvent;
import android.content.res.Resources;
import android.content.res.Configuration;

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

    public int getNavBarHeight() {
        int result = 0;

        boolean hasMenuKey = ViewConfiguration
                .get(this)
                .hasPermanentMenuKey();

        boolean hasBackKey = KeyCharacterMap
                .deviceHasKey(KeyEvent.KEYCODE_BACK);

        if(!hasMenuKey && !hasBackKey) {
            //The device has a navigation bar
            Resources resources = getResources();

            int orientation = resources
                    .getConfiguration().orientation;

            int resourceId = resources
                    .getIdentifier(orientation == Configuration.ORIENTATION_PORTRAIT
                            ? "navigation_bar_height"
                            : "navigation_bar_width",
                            "dimen",
                            "android");

            if (resourceId > 0) {
                return resources.getDimensionPixelSize(resourceId);
            }
        }
        return result;
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
