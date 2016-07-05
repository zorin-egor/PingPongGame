#include <jni.h>
#include <Common/Intersect.h>
#include "Main/Main.h"
#include "Common/Structures.h"

Main * game;

extern "C" {

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_init(JNIEnv* env, jobject obj, jint width, jint height, jobject pngManager, jobject assetManager){
        game = new Main(env, width, height, pngManager, assetManager);

//        GLfloat * polygons = new GLfloat[8];
//        polygons[0] = -0.5f;
//        polygons[1] = 0.25f;
//        polygons[2] = -0.5f;
//        polygons[3] = -0.5f;
//        polygons[4] = 0.25f;
//        polygons[5] = -0.5f;
//        polygons[6] = 0.25f;
//        polygons[7] = 0.25f;
//
//        GLfloat * polygons2 = new GLfloat[8];
//        polygons2[0] = 0.0f;
//        polygons2[1] = 0.5f;
//        polygons2[2] = 0.0f;
//        polygons2[3] = 0.0f;
//        polygons2[4] = 0.5f;
//        polygons2[5] = 0.0f;
//        polygons2[6] = 0.5f;
//        polygons2[7] = 0.5f;
//
//        Rectangle<GLfloat> rectangle;
//        rectangle.setRectangle(polygons);
//
//        Rectangle<GLfloat> rectangle2;
//        rectangle2.setRectangle(polygons2);
//
//        std::vector<GLfloat> crossRect;
//        bool iscrossRers = Intersect::intersectRect(&rectangle, &rectangle2, &crossRect);
//
//        Point<GLfloat> center = rectangle.getCenter();
//        Point<GLfloat> center2 = Rectangle<GLfloat>::getCenter(polygons);
//
//        GLfloat lineCenterx = rectangle.up.getCenterX();
//        GLfloat lineCentery = rectangle.up.getCenterY();
//
//        bool beetw = Intersect::between(-0.5f, 0.5f, 0.0f);
//        bool beetws = Intersect::betweenLine(&rectangle.up, 0.1f, 0.4f);
//
//        std::vector<GLfloat> crossP;
//        bool iscrossline = Intersect::intersectLines(&rectangle.left, &rectangle.up, &crossP);
//
//        std::vector<GLfloat> crossPPP;
//        *rectangle.left.x1 = -0.7f;
//        *rectangle.left.x2 = -0.7f;
//        bool iscrossSeg = Intersect::intersectSegments(&rectangle.left, &rectangle.up, &crossPPP);


    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_step(JNIEnv* env, jobject obj){
        game->step();
    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_action(JNIEnv* env, jobject obj, jfloat x, jfloat y, jboolean press){
        game->getLeft()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y));

        game->getRight()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                 Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y));

        if(press)
            game->getPlayPause()->action(Methods::convertCoordinatesToOpenGL(false, game->getWidth(), x),
                                         Methods::convertCoordinatesToOpenGL(true, game->getHeight(), y));
    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_pause(JNIEnv* env, jobject obj){

    }

    JNIEXPORT void JNICALL Java_ru_simpleapps_game_GameLib_stop(JNIEnv* env, jobject obj){

    }
}
