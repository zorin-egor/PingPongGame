package com.simpleapps.pingpong;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class GameActivity extends Activity {

    private GameView gameView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        gameView = new GameView(getApplicationContext());
        setContentView(gameView);
    }

    @Override
    protected void onStart() {
        super.onStart();
        gameView.start();
    }

    @Override
    protected void onStop() {
        super.onStop();
        gameView.stop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        gameView.destroy();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if (gameView.isBackPress()) {
                finish();
            }
            return true;
        }

        return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (gameView.touch(event)) {
            finish();
            return true;
        }
        
        return super.onTouchEvent(event);
    }

}
