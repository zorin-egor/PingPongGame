#ifndef GAME_PINGPONG_INIT_H
#define GAME_PINGPONG_INIT_H

#include <jni.h>
#include <stdlib.h>
#include <string>
#include <stdlib.h>

#include "Graphic/Objects/Platform/Platform.h"
#include "Graphic/Objects/Object.h"
#include "Graphic/Controls/Label.h"
#include "Graphic/Controls/Button.h"
#include "Particles/Particles.h"
#include "Shaders/MakeShaders.h"
#include "Graphic/View.h"
#include "Textures/ManageTexture.h"
#include "Common/Structures.h"
#include "Common/LogGL.h"

class Main {

    public:
        Main(   JNIEnv * _env, jint _width, jint _height, jobject _pngManager, jobject _assetManager) :
                env(_env),
                height(_height),
                width(_width),
                pngManager(_pngManager),
                assetManager(_assetManager)
        {
            deltaRotate = -3.14f;
            deltaStep = 0.1f;
            srand(static_cast <unsigned> (time(0)));
            init();
            createObjects();
        }

        ~Main(){
            delete matrix;
            delete background;
            delete left;
            delete playPause;
            delete right;
            delete textures;
            delete bordDown;
            delete field;
            delete player;
            delete bot;
        }

        void step();

        GLuint getPolygons(){
            return polygons;
        }

        GLuint getSprites(){
            return sprites;
        }

        Button * getLeft() const {
            return left;
        }

        Button * getRight() const {
            return right;
        }

        Button * getPlayPause() const {
            return playPause;
        }


        int getWidth() const {
            return width;
        }

        int getHeight() const {
            return height;
        }

        GLint getSpritesDelta() const {
            return spritesDelta;
        }

        GLint getSpritesPosition() const {
            return spritesPosition;
        }

        GLint getSpritesSize() const {
            return spritesSize;
        }

        GLint getSpritesColorStart() const {
            return spritesColorStart;
        }

        GLint getSpritesColorEnd() const {
            return spritesColorEnd;
        }

        GLint getPolygonsTransformationAttr() const {
            return polygonsTransformationAttr;
        }

        GLint getPolygonsTextureAttr() const {
            return polygonsTextureAttr;
        }

        GLint getPolygonsPositionAttr() const {
            return polygonsPositionAttr;
        }

    private:
        void init();
        void createObjects();
        void rotateBackground();
        GLfloat * setBordDownPosition(GLfloat * positionCoords);
        GLfloat * setBordUpPosition(GLfloat * positionCoords);
        void graphicInterface();

        Matrix * matrix;
        Particles * particles;

        // Screen
        int width;
        int height;

        // Java references
        JNIEnv * env;
        jobject pngManager;
        jobject assetManager;

        // Programs
        GLuint polygons;
        GLuint sprites;

        // Polygons
        GLint polygonsPositionAttr;
        GLint polygonsTextureAttr;
        GLint polygonsTransformationAttr;

        // Sprites
        GLint spritesPosition;

        GLint spritesDelta;
        GLint spritesSize;
        GLint spritesColorStart;
        GLint spritesColorEnd;

        // Objects
        View * background;
        View * center;
        View * bordDown;
        View * bordUp;
        Label * speed;
        Object * field;
        Platform * player;
        Platform * bot;

        Button * left;
        Button * playPause;
        Button * right;

        ManageTexture * textures;

        float deltaRotate;
        float deltaStep;
};


#endif //GAME_PINGPONG_INIT_H
