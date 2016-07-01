#include <jni.h>
#include <Common/Intersect.h>
#include "Main/Main.h"
#include "Common/Methods.h"

Main * game;


extern "C" {

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_init(JNIEnv* env, jobject obj, jint width, jint height, jobject pngManager, jobject assetManager){
//        game = new Main(env, width, height, pngManager, assetManager);

        std::vector<GLfloat> cross;

        GLfloat * rect1 = new GLfloat[8];
        rect1[0] = 0.0f;
        rect1[1] = 0.5f;
        rect1[2] = 0.0f;
        rect1[3] = 0.0f;
        rect1[4] = 0.5f;
        rect1[5] = 0.0f;
        rect1[6] = 0.5f;
        rect1[7] = 0.5f;

        GLfloat * rect2 = new GLfloat[8];
        rect2[0] = -0.5f;
        rect2[1] = 0.0f;
        rect2[2] = -0.5f;
        rect2[3] = -0.5f;
        rect2[4] = 0.0f;
        rect2[5] = -0.5f;
        rect2[6] = 0.0f;
        rect2[7] = 0.0f;

        bool intersect = Line::intersectRect(rect1, rect2, &cross);

//        GLfloat * line1 = new GLfloat[4];
//        line1[0] = 0.0f;
//        line1[1] = 0.0f;
//        line1[2] = 0.0f;
//        line1[3] = 0.5f;
//
//        GLfloat * line2 = new GLfloat[4];
//        line2[0] = -0.5f;
//        line2[1] = -0.5f;
//        line2[2] = 0.0f;
//        line2[3] = -0.5f;
//
//        bool flag = Line::intersect(line2, line1, &cross);

        bool equal = -0.0f == 0.0f;
    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_step(JNIEnv* env, jobject obj){
//        game->step();
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
