package ru.simpleapps.game;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

import java.util.HashMap;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameView extends GLSurfaceView {
    private static Context context;
    private HashMap<Integer, Integer> touchBuffer = new HashMap<>();
    public static boolean isGameOn = true;

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
                if(GameLib.action(event.getX(event.getActionIndex()), event.getY(event.getActionIndex()), event.getPointerId(event.getActionIndex()), true)){
                    isGameOn = false;
                    ((Activity)context).finish();
                }

                Log.d("Button", "COUNT: " + event.getPointerCount() +
                        "\nACTION INDEX: " + event.getActionIndex() +
                        "\nPOINTER ID: " + event.getPointerId(event.getActionIndex()) +
                        "\nFLAGS: " + event.getFlags());
                break;

            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP:
                GameLib.action(event.getX(event.getActionIndex()), event.getY(event.getActionIndex()), event.getPointerId(event.getActionIndex()), false);
                Log.d("Button", "COUNT: " + event.getPointerCount() +
                        "\nACTION INDEX: " + event.getActionIndex() +
                        "\nPOINTER ID: " + event.getPointerId(event.getActionIndex()) +
                        "\nFLAGS: " + event.getFlags());
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
            if(isGameOn)
                GameLib.step();
        }
    }
}
