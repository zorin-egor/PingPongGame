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

    JNIEXPORT jboolean JNICALL Java_ru_simpleapps_game_GameLib_action(JNIEnv* env, jobject obj, jfloat x, jfloat y, jint id, jboolean press){
        for (std::vector<Button *>::iterator it = game->getAllButtons()->begin(); it != game->getAllButtons()->end(); it++)
            (*it)->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x), Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y),
                          id, press);

        if( game->getExit()->getVisible() &&
            game->getExit()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                    Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y), id,press)){
            return true;
        }

        return false;
    }

    JNIEXPORT jboolean JNICALL Java_ru_simpleapps_game_GameLib_back(JNIEnv* env, jobject obj){
        return game->backAction();
    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_stop(JNIEnv* env, jobject obj){
        game->~Main();
    }
}
