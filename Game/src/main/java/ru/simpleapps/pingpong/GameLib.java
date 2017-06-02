package ru.simpleapps.pingpong;

import android.content.res.AssetManager;

public class GameLib {

    static{
        System.loadLibrary("PingPongGame");
    }

    public static native void init(int width, int height, PNGManager pngManager, AssetManager assetManager);
    public static native void step();
    public static native boolean action(float x, float y, int id, boolean press);
    public static native boolean back();
    public static native void stop();
}
