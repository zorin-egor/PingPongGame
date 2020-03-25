package ru.simpleapps.pingpong;

import android.content.Context;
import android.opengl.GLSurfaceView;

import java.lang.ref.WeakReference;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameRenderer implements GLSurfaceView.Renderer {

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
