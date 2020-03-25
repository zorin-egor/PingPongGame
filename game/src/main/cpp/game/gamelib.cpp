#include <jni.h>
#include <Common/Intersect.h>
#include <Main/Game.h>

#define JNI_METHOD(RTYPE, NAME) JNIEXPORT RTYPE JNICALL Java_ru_simpleapps_pingpong_GameLib_##NAME

Game* pGame = nullptr;

extern "C" {

    JNI_METHOD(void, init)(JNIEnv* env, jclass type, jobject pngManager, jobject assetManager) {
        pGame = new Game(env, pngManager, assetManager);
    }

    JNI_METHOD(void, destroy)(JNIEnv* env, jclass type) {
        delete pGame;
        pGame = nullptr;
    }

    JNI_METHOD(void, start)(JNIEnv* env, jclass type) {
        if (pGame != nullptr) {
            pGame->start();
        }
    }

    JNI_METHOD(void, stop)(JNIEnv* env, jclass type) {
        if (pGame != nullptr) {
            pGame->stop();
        }
    }

    JNI_METHOD(void, screen)(JNIEnv* env, jclass type, jint width, jint height) {
        if (pGame != nullptr) {
            pGame->screen(width, height);
        }
    }

    JNI_METHOD(void, step)(JNIEnv* env, jclass type) {
        if (pGame != nullptr) {
            pGame->step();
        }
    }

    JNI_METHOD(jboolean, action)(JNIEnv* env, jclass type, jfloat x, jfloat y, jint id, jboolean isPressed) {
        return pGame->action(x, y, id, isPressed);
    }

    JNI_METHOD(jboolean, isBackPress)(JNIEnv* env, jclass type) {
        return pGame != nullptr? pGame->isBackPress() : false;
    }

}
