package com.simpleapps.pingpong;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;


public class GameView extends GLSurfaceView {

    public GameView(Context context) {
        super(context);
        setEGLContextClientVersion(2);
        setRenderer(new GameRenderer(context));
    }

    public void start() {
        GameLib.start();
    }

    public void stop() {
        GameLib.stop();
    }

    public void destroy() {
        GameLib.destroy();
    }

    public boolean isBackPress() {
        return GameLib.isBackPress();
    }

    public boolean touch(final MotionEvent event) {
        switch (event.getActionMasked()) {
            case MotionEvent.ACTION_DOWN, MotionEvent.ACTION_POINTER_DOWN -> {
                return GameLib.action(
                        event.getX(event.getActionIndex()),
                        event.getY(event.getActionIndex()),
                        event.getPointerId(event.getActionIndex()),
                        true
                );
            }
            case MotionEvent.ACTION_UP, MotionEvent.ACTION_POINTER_UP -> {
                return GameLib.action(
                        event.getX(event.getActionIndex()),
                        event.getY(event.getActionIndex()),
                        event.getPointerId(event.getActionIndex()),
                        false
                );
            }
        }

        return false;
    }
}
