package ru.simpleapps.pingpong;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;

public class MainActivity extends Activity {

    GameView gameView;

    // Check git on linux
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        gameView = new GameView(this);
        setContentView(gameView);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        GameLib.stop();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if(GameLib.back()){
                finish();
            }

            return true;
        }
        return super.onKeyDown(keyCode, event);
    }
}
