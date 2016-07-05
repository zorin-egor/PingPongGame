#include <jni.h>
#include <Common/Intersect.h>
#include "Main/Main.h"
#include "Common/Structures.h"

Main * game;


extern "C" {

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_init(JNIEnv* env, jobject obj, jint width, jint height, jobject pngManager, jobject assetManager){
        //game = new Main(env, width, height, pngManager, assetManager);

        GLfloat * rect = new GLfloat[8];
        rect[0] = -0.5f;
        rect[1] = 0.5f;
        rect[2] = -0.5f;
        rect[3] = -0.5f;
        rect[4] = 0.5f;
        rect[5] = -0.5f;
        rect[6] = 0.5f;
        rect[7] = 0.5f;

        Rectangle<GLfloat> rectangle(rect);

        GLfloat test1X = *rectangle.left.x1;

        rect[0] = 1.5f;

        GLfloat test2X = *rectangle.left.x1;
    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_step(JNIEnv* env, jobject obj){
        //game->step();
    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_action(JNIEnv* env, jobject obj, jfloat x, jfloat y, jboolean press){
//        game->getLeft()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
//                                Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y));
//
//        game->getRight()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
//                                 Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y));
//
//        if(press)
//            game->getPlayPause()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
//                                         Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y));
    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_pause(JNIEnv* env, jobject obj){

    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_stop(JNIEnv* env, jobject obj){

    }
}
