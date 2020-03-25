package ru.simpleapps.pingpong;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class GameActivity extends Activity {

    private GameView mGameView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGameView = new GameView(getApplicationContext());
        setContentView(mGameView);
    }

    @Override
    protected void onStart() {
        super.onStart();
        mGameView.start();
    }

    @Override
    protected void onStop() {
        super.onStop();
        mGameView.stop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mGameView.destroy();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if (mGameView.isBackPress()) {
                finish();
            }
            return true;
        }

        return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (mGameView.touch(event)) {
            finish();
            return true;
        }

        return super.onTouchEvent(event);
    }

}
