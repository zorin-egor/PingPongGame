#ifndef GAME_H
#define GAME_H

#include <jni.h>
#include <stdlib.h>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <unistd.h>

#include "../Graphic/Objects/Platform/Enemy.h"
#include "../Graphic/Objects/Ball/Ball.h"
#include "../Graphic/Objects/Platform/Platform.h"
#include "../Graphic/Objects/Object.h"
#include "../Graphic/Controls/Label.h"
#include "../Graphic/Controls/Button.h"
#include "../Particles/Particles.h"
#include "../Particles/Splash.h"
#include "../Particles/Plume.h"
#include "../Particles/Shape.h"
#include "../Shaders/MakeShaders.h"
#include "../Graphic/View.h"
#include "../Textures/TexturesManager.h"
#include "../Common/Structures.h"
#include "../Common/LogGL.h"
#include "../Sound/OSLSound.h"

#include "Main/State.h"

/*
 * TODO Refactoring jni
 * TODO Refactoring opengl
 * TODO Refactoring opensl
 * */
class Game {

    public:

        static const float CENTER_ROTATE;
        static const float CENTER_SPEED;
        static const float CENTER_PERIOD;
        static const float BORDER_UP;
        static const float BORDER_DOWN;
        static const float NEGATIVE;
        static const float BUTTON_CONTROL_HEIGHT;
        static const float BUTTON_CONTROL_WIDTH;
        static const float BUTTON_START_HEIGHT;
        static const float BUTTON_START_WIDTH;
        static const float PLATFORMS_WIDTH;
        static const float PLATFORMS_HEIGHT;
        static const float PLATFORMS_SPEED;
        static const float BALL_WIDTH;
        static const float BALL_SPEED;
        static const float STOP_MOVE;
        static const float LABEL_HEIGHT;
        static const float LABEL_WIDTH;
        static const float BUTTON_MENU_WIDTH;
        static const float BUTTON_MENU_HEIGHT;
        static const float BUTTON_MENU_X_POSITION;


    private:

        State m_oGameState;

        std::vector<Button*> m_oButtons;
        std::vector<Button*> m_oMenuButtons;

        Matrix * m_pMatrix;
        OSLSound * m_pOSLSound;
        TexturesManager * m_pTextures;

        // Screen
        int m_nWidth;
        int m_nHeight;
        float m_fScreenRatio;
        float m_fBallWidth;

        // Programs
        GLuint m_nPolygons;
        GLuint m_nSprites;
        GLuint m_nSplash;
        GLuint m_nShape;

        // Polygons
        GLint m_nPolygonsPositionAttr;
        GLint m_nPolygonsTextureAttr;
        GLint m_nPolygonsTransformationAttr;

        // Sprites
        GLint m_nSpritesRandomPosition;
        GLint m_nSpritesRandomSpeed;
        GLint m_nSpritesRandomRadius;
        GLint m_nSpritesTotalDeltaSpeed;
        GLint m_nSpritesDelta;
        GLint m_nSpritesSize;
        GLint m_nSpritesColorStart;
        GLint m_nSpritesColorEnd;

        // Splash
        GLint m_nSplashPosition;
        GLint m_nSplashColorStart;
        GLint m_nSplashColorEnd;
        GLint m_nSplashDelta;
        GLint m_nSplashSize;

        // Shape
        GLint m_nShapeAngle;
        GLint m_nShapeColor;
        GLint m_nShapeCenter;
        GLint m_nShapeRadius;
        GLint m_nShapeArguments;
        GLint m_nShapeSize;
        GLint m_nShapeTotalDeltaSpeed;

        // Particles
        Particles * m_pParticles;
        Splash * m_pSplash;
        Plume * m_pPlume;
        Shape * m_pShape;

        // Common
        View * m_pBordDown;
        View * m_pMenuHeader;

        Object * m_pField;
        Ball * m_pBall;
        Button * m_pLeft;
        Button * m_pPlayPause;
        Button * m_pRight;

        // For single
        Label * m_pSingleSpeed;
        Label * m_pSingleScoreOne;
        Label * m_pSingleScoreTwo;
        View * m_pBordUp;
        Platform * m_pPlayer;
        Platform * m_pPlayerTwo;
        Enemy * m_pEnemy;

        // For multi
        Label * m_pMultiScoreOne;
        Label * m_pMultiScoreTwo;
        Button * m_pLeftTwo;
        Button * m_pPlayPauseTwo;
        Button * m_pRightTwo;
        View * m_pBordDownTwo;

        // For menu
        Button * m_pSingle;
        Button * m_pMulti;
        Button * m_pSound;
        Button * m_pQuality;
        Button * m_pExit;

    public:

        Game(JNIEnv * env, jobject pngManager, jobject assetManager);

        ~Game();

        void start();

        void stop();

        void screen(uint width, uint height);

        void step();

        bool isBackPress();

        GLuint getPolygons() {
            return m_nPolygons;
        }

        GLuint getSprites() {
            return m_nSprites;
        }

        Button * getLeft() const {
            return m_pLeft;
        }

        Button * getRight() const {
            return m_pRight;
        }

        Button * getPlayPause() const {
            return m_pPlayPause;
        }

        Button * getLeftTwo() const {
            return m_pLeftTwo;
        }

        Button * getRightTwo() const {
            return m_pRightTwo;
        }

        Button * getPlayPauseTwo() const {
            return m_pPlayPauseTwo;
        }

        Button * getSingle() const {
            return m_pSingle;
        }

        Button * getMulti() const {
            return m_pMulti;
        }

        Button * getSound() const {
            return m_pSound;
        }

        Button * getExit() const {
            return m_pExit;
        }

        int getWidth() const {
            return m_nWidth;
        }

        int getHeight() const {
            return m_nHeight;
        }

        std::vector<Button*>* getButtons() {
            return &m_oButtons;
        }

        void setGameState(const State &gameState) {
            Game::m_oGameState = gameState;
        }

        GLint getSpritesDelta() const {
            return m_nSpritesDelta;
        }

        GLint getSpritesSize() const {
            return m_nSpritesSize;
        }

        GLint getSpritesColorStart() const {
            return m_nSpritesColorStart;
        }

        GLint getSpritesColorEnd() const {
            return m_nSpritesColorEnd;
        }

        GLint getPolygonsTransformationAttr() const {
            return m_nPolygonsTransformationAttr;
        }

        GLint getPolygonsTextureAttr() const {
            return m_nPolygonsTextureAttr;
        }

        GLint getPolygonsPositionAttr() const {
            return m_nPolygonsPositionAttr;
        }

        GLint getSpritesRandomPosition() const {
            return m_nSpritesRandomPosition;
        }

        GLint getSpritesRandomSpeed() const {
            return m_nSpritesRandomSpeed;
        }

        GLint getSpritesRandomRadius() const {
            return m_nSpritesRandomRadius;
        }

        GLint getSpritesTotalDeltaSpeed() const {
            return m_nSpritesTotalDeltaSpeed;
        }


    private:

        bool init(JNIEnv * env, jobject pngManager, jobject assetManager);

        void setDefault();

        void setMenuButtonsVisibility(bool isVisible);

        void createTextureObjects();

        void destroyTextureObjects();

        void renderBackground();

        GLfloat * setBordDownPosition(GLfloat * positionCoords, bool isInverse);

        GLfloat * setBordUpPosition(GLfloat * positionCoords);

        void drawFrameForSingle();

        void logicSingle();

        void renderSingleInterface();

        void renderSingleObjects();

        void drawFrameForMulti();

        void logicMulti();

        void renderMultiInterface();

        void renderMultiObjects();

        void drawFrameMenu();

        void logicMenu();

        void lowQuality();

        void highQuality();
};


#endif
