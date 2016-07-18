#include <jni.h>
#include <Common/Intersect.h>
#include "Main/Main.h"
#include "Common/Structures.h"

Main * game;

extern "C" {

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_init(JNIEnv* env, jobject obj, jint width, jint height, jobject pngManager, jobject assetManager){
        game = new Main(env, width, height, pngManager, assetManager);
    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_step(JNIEnv* env, jobject obj){
        game->step();
    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_action(JNIEnv* env, jobject obj, jfloat x, jfloat y, jint id, jboolean press){
        game->getLeft()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y),
                                id,
                                press);

        game->getRight()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                 Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y),
                                 id,
                                 press);

        game->getPlayPause()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                     Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y),
                                     id,
                                     press);

        game->getLeftTwo()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y),
                                id,
                                press);

        game->getRightTwo()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                     Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y),
                                     id,
                                     press);

        game->getPlayPauseTwo()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                         Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y),
                                         id,
                                         press);

        game->getSingle()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y),
                                id,
                                press);

        game->getMulti()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y),
                                id,
                                press);
    }

    JNIEXPORT jboolean JNICALL Java_ru_simpleapps_game_GameLib_back(JNIEnv* env, jobject obj){
        return game->backAction();
    }
}
