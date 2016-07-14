package ru.simpleapps.game;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;

public class MainActivity extends Activity {

    GameView gameView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        gameView = new GameView(getApplication());
        setContentView(gameView);
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onStop() {
        super.onStop();
        GameLib.stop();
        finish();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if(GameLib.stop()){
                finish();
            }
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }
}
