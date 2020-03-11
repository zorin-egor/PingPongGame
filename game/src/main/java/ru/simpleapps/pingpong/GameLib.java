package ru.simpleapps.pingpong;

import android.content.res.AssetManager;

public class GameLib {

    static {
        System.loadLibrary(BuildConfig.LIB_GAME);
    }

    public static native void init(BitmapManager bitmapManager, AssetManager assetManager);

    public static native void destroy();

    public static native void start();

    public static native void stop();

    public static native void screen(int width, int height);

    public static native void step();

    public static native boolean action(float x, float y, int id, boolean press);

    public static native boolean isBackPress();



}
