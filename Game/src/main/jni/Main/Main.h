#ifndef GAME_PINGPONG_INIT_H
#define GAME_PINGPONG_INIT_H

#include <jni.h>
#include <stdlib.h>
#include <string>
#include <stdlib.h>

#include "Graphic/Objects/Platform/Enemy.h"
#include "Graphic/Objects/Ball/Ball.h"
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
                assetManager(_assetManager),

                CENTER_ROTATE(3.14f),
                CENTER_SPEED(0.005f),
                CENTER_PERIOD(-3.14f),
                BORDER_UP(0.8f),
                BORDER_DOWN(-0.6f),
                NEGATIVE(-1.0f),
                BUTTON_CONTROL_HEIGHT(0.2f),
                BUTTON_CONTROL_WIDTH(0.7f),
                BUTTON_START_HEIGHT(0.2f),
                BUTTON_START_WIDTH(0.5f),
                PLATFORMS_WIDTH(0.6f),
                PLATFORMS_HEIGHT(0.2f),
                PLATFORMS_SPEED(0.04f),
                BALL_WIDTH(PLATFORMS_WIDTH / 5.0f),
                BALL_HEIGHT(((float)_width / (float)_height) * BALL_WIDTH),
                BALL_SPEED(0.02f),
                STOP_MOVE(0.0f),
                LABEL_HEIGHT(0.1f),
                LABEL_WIDTH(1.0f)
        {
            deltaRotate = -3.14f;
            srand(static_cast<unsigned> (time(0)));
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
            delete enemy;
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

        void renderBackground();
        void renderInterface();
        void renderObjects();

        GLfloat * setBordDownPosition(GLfloat * positionCoords);
        GLfloat * setBordUpPosition(GLfloat * positionCoords);
        void drawFrame();
        void logic();

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
        Enemy * enemy;
        Ball * ball;

        Button * left;
        Button * playPause;
        Button * right;

        ManageTexture * textures;

        float deltaRotate;

        const float CENTER_ROTATE;
        const float CENTER_SPEED;
        const float CENTER_PERIOD;
        const float BORDER_UP;
        const float BORDER_DOWN;
        const float NEGATIVE;
        const float BUTTON_CONTROL_HEIGHT;
        const float BUTTON_CONTROL_WIDTH;
        const float BUTTON_START_HEIGHT;
        const float BUTTON_START_WIDTH;
        const float PLATFORMS_WIDTH;
        const float PLATFORMS_HEIGHT;
        const float PLATFORMS_SPEED;
        const float BALL_WIDTH;
        const float BALL_HEIGHT;
        const float BALL_SPEED;
        const float STOP_MOVE;
        const float LABEL_HEIGHT;
        const float LABEL_WIDTH;
};


#endif //GAME_PINGPONG_INIT_H
