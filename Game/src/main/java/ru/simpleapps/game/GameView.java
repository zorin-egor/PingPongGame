package ru.simpleapps.game;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameView extends GLSurfaceView {
    private static Context context;

    public GameView(Context context) {
        super(context);
        this.context = context;
        setEGLContextClientVersion(2);
        setRenderer(new GameRenderer());
    };

    @Override
    public boolean onTouchEvent(final MotionEvent event) {
        switch(event.getActionMasked()){
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_POINTER_DOWN:
                GameLib.action(event.getX(), event.getY(), true);
                break;

            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP:
                GameLib.action(event.getX(), event.getY(), false);
                break;
        }

        return true;
    }

    private static class GameRenderer implements GLSurfaceView.Renderer{

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            GameLib.init(width, height, new PNGManager(context.getAssets()), context.getAssets());
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            GameLib.step();
        }
    }
}
