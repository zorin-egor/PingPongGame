package ru.simpleapps.game;

import android.content.res.AssetManager;

public class GameLib {

    static{
        System.loadLibrary("SimpleGame");
    }

    public static native void init(int width, int height, PNGManager pngManager, AssetManager assetManager);
    public static native void step();
    public static native void action(float x, float y, int id, boolean press);
    public static native boolean stop();
}
