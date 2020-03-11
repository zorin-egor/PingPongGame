package ru.simpleapps.pingpong;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import java.lang.ref.WeakReference;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

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
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_POINTER_DOWN:
                return GameLib.action(
                        event.getX(event.getActionIndex()),
                        event.getY(event.getActionIndex()),
                        event.getPointerId(event.getActionIndex()),
                        true
                );

            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP:
                return GameLib.action(
                        event.getX(event.getActionIndex()),
                        event.getY(event.getActionIndex()),
                        event.getPointerId(event.getActionIndex()),
                        false
                );
        }

        return false;
    }

    private static class GameRenderer implements GLSurfaceView.Renderer {

        private WeakReference<Context> mContext;

        public GameRenderer(Context context) {
            mContext = new WeakReference<>(context);
        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            final Context context = mContext.get();
            if (context != null) {
                GameLib.init(new BitmapManager(context.getAssets()), context.getAssets());
            } else {
                throw new IllegalStateException("Context must be set!");
            }
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            GameLib.screen(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            GameLib.step();
        }
    }
}
