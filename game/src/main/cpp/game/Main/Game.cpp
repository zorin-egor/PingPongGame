#include "Game.h"

const float Game::CENTER_ROTATE = 3.14f;
const float Game::CENTER_SPEED = 0.005f;
const float Game::CENTER_PERIOD = -3.14f;
const float Game::BORDER_UP = 0.8f;
const float Game::BORDER_DOWN = -0.57f;
const float Game::NEGATIVE = -1.0f;
const float Game::BUTTON_CONTROL_HEIGHT = 0.22f;
const float Game::BUTTON_CONTROL_WIDTH = 0.7f;
const float Game::BUTTON_START_HEIGHT = 0.12f;
const float Game::BUTTON_START_WIDTH = 0.5f;
const float Game::PLATFORMS_WIDTH = 0.5f;
const float Game::PLATFORMS_HEIGHT = 0.1f;
const float Game::PLATFORMS_SPEED = 0.06f;
const float Game::BALL_WIDTH = PLATFORMS_WIDTH / 5.0f;
const float Game::BALL_SPEED = 0.02f;
const float Game::STOP_MOVE = 0.0f;
const float Game::LABEL_HEIGHT = 0.1f;
const float Game::LABEL_WIDTH = 0.5f;
const float Game::BUTTON_MENU_WIDTH = 1.4f;
const float Game::BUTTON_MENU_HEIGHT = 0.32f;
const float Game::BUTTON_MENU_X_POSITION = (2.0f - 1.4f) / 2.0f - 1.0f;


Game::Game(JNIEnv *env, jobject pngManager, jobject assetManager) {
    LOGI("Game::Game()");
    m_oGameState = State::MENU;

    m_nWidth = 0;
    m_nHeight = 0;

    m_pMatrix = nullptr;
    m_pParticles = nullptr;
    m_pSplash = nullptr;
    m_pPlume = nullptr;
    m_pShape = nullptr;
    m_pOSLSound = nullptr;
    m_pBordDown = nullptr;
    m_pMenuHeader = nullptr;
    m_pField = nullptr;
    m_pBall = nullptr;
    m_pLeft = nullptr;
    m_pPlayPause = nullptr;
    m_pRight = nullptr;
    m_pSingleSpeed = nullptr;
    m_pSingleScoreOne = nullptr;
    m_pSingleScoreTwo = nullptr;
    m_pBordUp = nullptr;
    m_pPlayer = nullptr;
    m_pPlayerTwo = nullptr;
    m_pEnemy = nullptr;
    m_pMultiScoreOne = nullptr;
    m_pMultiScoreTwo = nullptr;
    m_pLeftTwo = nullptr;
    m_pPlayPauseTwo = nullptr;
    m_pRightTwo = nullptr;
    m_pBordDownTwo = nullptr;
    m_pSingle = nullptr;
    m_pMulti = nullptr;
    m_pSound = nullptr;
    m_pQuality = nullptr;
    m_pExit = nullptr;
    m_pTextures = nullptr;

    srand(static_cast<unsigned>(time(0)));
    init(env, pngManager, assetManager);
}

Game::~Game() {
    LOGI("Game::~Game()");
    m_pOSLSound->stopAll();
    destroyTextureObjects();
    delete m_pMatrix;
    delete m_pOSLSound;
    delete m_pTextures;
}

void Game::start() {
    m_pOSLSound->play(OSLSound::BACKGROUND);
}

void Game::stop() {
    m_pOSLSound->stopAll();
}

void Game::screen(uint width, uint height) {
    auto isResize = m_nWidth != width || m_nHeight != height;

    m_nWidth = width;
    m_nHeight = height;
    m_fScreenRatio = (float)width / (float)height;
    m_fBallWidth = m_fScreenRatio * BALL_WIDTH;

    glViewport(0, 0, m_nWidth, m_nHeight);
    checkGLError("Game::screen - glViewport");

    if (isResize) {
        destroyTextureObjects();
        createTextureObjects();
    }
}

void Game::step() {
    // Clear screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    checkGLError("Game::m_fStep - glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGLError("Game::m_fStep - glClear");

    // Draw background everywhere
    renderBackground();

    // Main state of application
    switch(m_oGameState) {
        case State::MENU:
            logicMenu();
            // Draw
            drawFrameMenu();
            break;

        case State::SINGLE:
            // Logic
            if (m_pPlayPause->getState()) {
                logicSingle();
            }

            // Draw
            drawFrameForSingle();
            break;

        case State::MULTI:
            // Logic
            if (m_pPlayPause->getState() && m_pPlayPauseTwo->getState()) {
                logicMulti();
            }

            // Draw
            drawFrameForMulti();
            break;
    }
}

bool Game::isBackPress() {
    switch (m_oGameState) {
        case State::SINGLE:
        case State::MULTI:
            setDefault();
            m_oGameState = State::MENU;
            return false;
        case State::MENU:
            return true;
    }
}

bool Game::action(uint x, uint y, int id, bool isPressed) {
    std::for_each(getButtons()->begin(), getButtons()->end(), [&](std::vector<Button*>::value_type &item) {
        item->action(Methods::convertCoordinatesToOpenGL(false, getWidth(), x),
                Methods::convertCoordinatesToOpenGL(true, getHeight(), y),
                id, isPressed);
    });

    if (getExit()->getVisible() &&
        getExit()->action(Methods::convertCoordinatesToOpenGL(false, getWidth(), x),
                          Methods::convertCoordinatesToOpenGL(true, getHeight(), y), id, isPressed)) {
        return true;
    }

    return false;
}

bool Game::init(JNIEnv* env, jobject pngManager, jobject assetManager) {
    // Matrix helper
    m_pMatrix = new Matrix();

    // Create sound class
    m_pOSLSound = new OSLSound(env, assetManager, false);

    // Create texture manager
    m_pTextures = new TexturesManager(env, pngManager, assetManager);

    // Polygons
    m_nPolygons = MakeShaders::createProgram(MakeShaders::V_MAIN_SHADER, MakeShaders::F_MAIN_SHADER);
    if (m_nPolygons == 0) {
        return false;
    }

    m_nPolygonsPositionAttr = glGetAttribLocation(m_nPolygons, "a_Position");
    checkGLError("Game::init - m_nPolygons - a_Position");
    m_nPolygonsTextureAttr = glGetAttribLocation(m_nPolygons, "a_Texture");
    checkGLError("Game::init - m_nPolygons - a_Texture");
    m_nPolygonsTransformationAttr = glGetUniformLocation(m_nPolygons, "u_Matrix");
    checkGLError("Game::init - m_nPolygons - u_Matrix");

    // Sprites
    m_nSprites = MakeShaders::createProgram(MakeShaders::V_POINT_SHADER, MakeShaders::F_POINT_SHADER);
    if (m_nSprites == 0) {
        return false;
    }

    m_nSpritesRandomPosition = glGetAttribLocation(m_nSprites, "a_RandomArrayCoords");
    checkGLError("Game::init - m_nSprites - a_RandomArrayCoords");
    m_nSpritesRandomSpeed = glGetAttribLocation(m_nSprites, "a_RandomArraySpeed");
    checkGLError("Game::init - m_nSprites - a_RandomArraySpeed");
    m_nSpritesRandomRadius = glGetAttribLocation(m_nSprites, "a_RandomArrayRadius");
    checkGLError("Game::init - m_nSprites - a_RandomArrayRadius");
    m_nSpritesDelta = glGetAttribLocation(m_nSprites, "a_Delta");
    checkGLError("Game::init - m_nSprites - a_Delta");
    m_nSpritesSize = glGetUniformLocation(m_nSprites, "u_Size");
    checkGLError("Game::init - m_nSprites - u_Size");
    m_nSpritesTotalDeltaSpeed = glGetUniformLocation(m_nSprites, "u_TotalDeltaSpeed");
    checkGLError("Game::init - m_nSprites - u_TotalDeltaSpeed");
    m_nSpritesColorStart = glGetAttribLocation(m_nSprites, "a_ColorStart");
    checkGLError("Game::init - m_nSprites - a_ColorStart");
    m_nSpritesColorEnd = glGetAttribLocation(m_nSprites, "a_ColorEnd");
    checkGLError("Game::init - m_nSprites - a_ColorEnd");

    // Splash
    m_nSplash = MakeShaders::createProgram(MakeShaders::V_SPLASH_SHADER, MakeShaders::F_SPLASH_SHADER);
    if (m_nSplash == 0) {
        return false;
    }

    m_nSplashPosition = glGetAttribLocation(m_nSplash, "a_ArrayCoords");
    checkGLError("Game::init - m_nSplash - a_ArrayCoords");
    m_nSplashColorStart = glGetAttribLocation(m_nSplash, "a_ColorStart");
    checkGLError("Game::init - m_nSplash - a_ColorStart");
    m_nSplashColorEnd = glGetAttribLocation(m_nSplash, "a_ColorEnd");
    checkGLError("Game::init - m_nSplash - a_ColorEnd");
    m_nSplashDelta = glGetAttribLocation(m_nSplash, "a_Delta");
    checkGLError("Game::init - m_nSplash - a_Delta");
    m_nSplashSize = glGetUniformLocation(m_nSplash, "u_Size");
    checkGLError("Game::init - m_nSplash - u_Size");

    // Shape
    m_nShape = MakeShaders::createProgram(MakeShaders::V_SHAPE_SHADER, MakeShaders::F_SHAPE_SHADER);
    if (m_nShape == 0) {
        return false;
    }

    m_nShapeAngle = glGetAttribLocation(m_nShape, "a_ArrayAngle");
    checkGLError("Game::init - m_nShape - a_ArraySpeed");
    m_nShapeColor = glGetAttribLocation(m_nShape, "a_ArrayColor");
    checkGLError("Game::init - m_nShape - a_ArrayColor");
    m_nShapeCenter = glGetUniformLocation(m_nShape, "u_Center");
    checkGLError("Game::init - m_nShape - u_Center");
    m_nShapeRadius = glGetUniformLocation(m_nShape, "u_Radius");
    checkGLError("Game::init - m_nShape - u_Radius");
    m_nShapeArguments = glGetUniformLocation(m_nShape, "u_Arguments");
    checkGLError("Game::init - m_nShape - u_Arguments");
    m_nShapeSize = glGetUniformLocation(m_nShape, "u_PointSize");
    checkGLError("Game::init - m_nShape - u_PointSize");
    m_nShapeTotalDeltaSpeed = glGetUniformLocation(m_nShape, "u_TotalDeltaSpeed");
    checkGLError("Game::init - m_nShape - u_TotalDeltaSpeed");

    // Clear compilers
    glReleaseShaderCompiler();

    //On alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkGLError("Game::init - glBlendFunc");
    glEnable(GL_BLEND);
    checkGLError("Game::init - glEnable");

    return true;
}

void Game::setDefault() {
    // Reset splash
    m_pSplash->resetTimer();

    // Set background shape
    m_pShape->setSettings();

    // PLayers buttons
    m_pPlayPause->setState(false);
    m_pPlayPauseTwo->setState(false);

    // Score labels
    m_pPlayer->clearScore();
    m_pPlayerTwo->clearScore();
    m_pEnemy->clearScore();

    // Players positions
    m_pPlayer->setDefaultPosition();
    m_pPlayerTwo->setDefaultPosition();
    m_pEnemy->setDefaultPosition();

    // Balls positions
    m_pBall->setIsOut(false);
    m_pBall->setDefaultPosition();
    m_pBall->resetSpeed();

    // Change labels values
    m_pSingleSpeed->setNumber(Methods::fillLeft(Methods::intToString(0), '0', 3));
    m_pSingleScoreOne->setNumber(Methods::fillLeft(Methods::intToString((0)), '0', 3));
    m_pSingleScoreOne->setNumber(Methods::fillLeft(Methods::intToString((0)), '0', 3));
    m_pMultiScoreOne->setNumber(Methods::fillLeft(Methods::intToString(0), '0', 3));
    m_pMultiScoreTwo->setNumber(Methods::fillLeft(Methods::intToString(0), '0', 3));
}

void Game::setMenuButtonsVisibility(bool isVisible) {
    std::for_each(m_oMenuButtons.begin(), m_oMenuButtons.end(), [&](std::vector<Button*>::value_type &item) {
        item->setVisible(isVisible);
    });
}

void Game::createTextureObjects() {
    // Background shape
    m_pShape = new Shape(15000,
                         0.0f,
                         0.0f,
                         0.3f / m_fScreenRatio,
                         0.3f,
                         m_nShape,
                         m_pTextures->getTextureId(TexturesManager::PARTICLES),
                         m_nShapeAngle,
                         m_nShapeColor,
                         m_nShapeCenter,
                         m_nShapeRadius,
                         m_nShapeArguments,
                         m_nShapeSize,
                         m_nShapeTotalDeltaSpeed);

    // Background stars
    m_pParticles = new Particles(3000,
                                 m_nSprites,
                                 m_pTextures->getTextureId(TexturesManager::PARTICLES),
                                 m_nSpritesRandomPosition,
                                 m_nSpritesRandomSpeed,
                                 m_nSpritesRandomRadius,
                                 m_nSpritesDelta,
                                 m_nSpritesColorStart,
                                 m_nSpritesColorEnd,
                                 m_nSpritesSize,
                                 m_nSpritesTotalDeltaSpeed);

    // Splash by collisions
    m_pSplash = new Splash(200, 50,
                           m_nSplash,
                           m_pTextures->getTextureId(TexturesManager::SPLASH),
                           m_nSplashPosition,
                           m_nSplashColorStart,
                           m_nSplashColorEnd,
                           m_nSplashDelta,
                           m_nSplashSize);

    // Plume from ball
    m_pPlume = new Plume(350,
                         m_nSplash,
                         m_pTextures->getTextureId(TexturesManager::PLUME),
                         m_nSplashPosition,
                         m_nSplashColorStart,
                         m_nSplashColorEnd,
                         m_nSplashDelta,
                         m_nSplashSize);

    // Bord down
    m_pBordDown = new View(m_pTextures->getTextureId(TexturesManager::BORDERS),
                           m_nPolygons,
                           m_nPolygonsPositionAttr,
                           m_nPolygonsTextureAttr,
                           m_nPolygonsTransformationAttr,
                           setBordDownPosition(m_pMatrix->getDefaultVerticesCoords(), false),
                           Matrix::setTextureCoords(m_pMatrix->getDefaultTextureCoord(), 1, 2, Matrix::TWO),
                           m_pMatrix->getDefaultMatrix4x4());

    // Bord down for player two
    m_pBordDownTwo = new View(m_pTextures->getTextureId(TexturesManager::BORDERS),
                              m_nPolygons,
                              m_nPolygonsPositionAttr,
                              m_nPolygonsTextureAttr,
                              m_nPolygonsTransformationAttr,
                              setBordDownPosition(m_pMatrix->getDefaultVerticesCoords(), true),
                              Matrix::rotateTextureCoord(Matrix::setTextureCoords(m_pMatrix->getDefaultTextureCoord(), 1, 2, Matrix::TWO), 2),
                              m_pMatrix->getDefaultMatrix4x4());

    // Bord up
    m_pBordUp = new View(m_pTextures->getTextureId(TexturesManager::BORDERS),
                         m_nPolygons,
                         m_nPolygonsPositionAttr,
                         m_nPolygonsTextureAttr,
                         m_nPolygonsTransformationAttr,
                         setBordUpPosition(m_pMatrix->getDefaultVerticesCoords()),
                         Matrix::setTextureCoords(m_pMatrix->getDefaultTextureCoord(), 1, 2, Matrix::ONE),
                         m_pMatrix->getDefaultMatrix4x4());

    // Left button
    m_pLeft = new Button(false,
                         true,
                         false,
                         -0.88f, -0.76f, BUTTON_CONTROL_HEIGHT / m_fScreenRatio, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
                         m_pTextures->getTextureId(TexturesManager::BUTTONS),
                         m_nPolygons,
                         m_nPolygonsPositionAttr,
                         m_nPolygonsTextureAttr,
                         m_nPolygonsTransformationAttr,
                         m_pMatrix->getDefaultVerticesCoords(),
                         m_pMatrix->getDefaultTextureCoord(),
                         m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pLeft);

    // Right button
    m_pRight = new Button(false,
                          true,
                          false,
                          0.52f, -0.76f, BUTTON_CONTROL_HEIGHT / m_fScreenRatio, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
                          m_pTextures->getTextureId(TexturesManager::BUTTONS),
                          m_nPolygons,
                          m_nPolygonsPositionAttr,
                          m_nPolygonsTextureAttr,
                          m_nPolygonsTransformationAttr,
                          m_pMatrix->getDefaultVerticesCoords(),
                          m_pMatrix->getDefaultTextureCoord(),
                          m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pRight);

    // Play pause button
    m_pPlayPause = new Button(true,
                              false,
                              false,
                              -0.25f, -0.72f, BUTTON_START_WIDTH, BUTTON_START_HEIGHT, 4, 4, Matrix::FOUR, Matrix::THREE,
                              m_pTextures->getTextureId(TexturesManager::BUTTONS),
                              m_nPolygons,
                              m_nPolygonsPositionAttr,
                              m_nPolygonsTextureAttr,
                              m_nPolygonsTransformationAttr,
                              m_pMatrix->getDefaultVerticesCoords(),
                              m_pMatrix->getDefaultTextureCoord(),
                              m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pPlayPause);

    // Left button player two
    m_pLeftTwo = new Button(false,
                            true,
                            true,
                            -0.88f, 0.76f + BUTTON_CONTROL_HEIGHT, BUTTON_CONTROL_HEIGHT / m_fScreenRatio, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
                            m_pTextures->getTextureId(TexturesManager::BUTTONS),
                            m_nPolygons,
                            m_nPolygonsPositionAttr,
                            m_nPolygonsTextureAttr,
                            m_nPolygonsTransformationAttr,
                            m_pMatrix->getDefaultVerticesCoords(),
                            m_pMatrix->getDefaultTextureCoord(),
                            m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pLeftTwo);

    // Right button player two
    m_pRightTwo = new Button(false,
                             true,
                             true,
                             0.52f, 0.76f + BUTTON_CONTROL_HEIGHT, BUTTON_CONTROL_HEIGHT / m_fScreenRatio, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
                             m_pTextures->getTextureId(TexturesManager::BUTTONS),
                             m_nPolygons,
                             m_nPolygonsPositionAttr,
                             m_nPolygonsTextureAttr,
                             m_nPolygonsTransformationAttr,
                             m_pMatrix->getDefaultVerticesCoords(),
                             m_pMatrix->getDefaultTextureCoord(),
                             m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pRightTwo);

    // Play pause button player two
    m_pPlayPauseTwo = new Button(true,
                                 false,
                                 true,
                                 -0.25f, 0.72f + BUTTON_START_HEIGHT, BUTTON_START_WIDTH, BUTTON_START_HEIGHT, 4, 4, Matrix::FOUR, Matrix::THREE,
                                 m_pTextures->getTextureId(TexturesManager::BUTTONS),
                                 m_nPolygons,
                                 m_nPolygonsPositionAttr,
                                 m_nPolygonsTextureAttr,
                                 m_nPolygonsTransformationAttr,
                                 m_pMatrix->getDefaultVerticesCoords(),
                                 m_pMatrix->getDefaultTextureCoord(),
                                 m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pPlayPauseTwo);

    // Label of singleSpeed
    m_pSingleSpeed = new Label(m_pMatrix,
                               -0.25f, 0.97f, LABEL_WIDTH, LABEL_HEIGHT,
                               m_pTextures->getTextureId(TexturesManager::NUMBERS),
                               m_nPolygons,
                               m_nPolygonsPositionAttr,
                               m_nPolygonsTextureAttr,
                               m_nPolygonsTransformationAttr,
                               "000",
                               false);

    // Label of score one for single
    m_pSingleScoreOne = new Label(m_pMatrix,
                                  -0.91f, 0.97f, LABEL_WIDTH, LABEL_HEIGHT,
                                  m_pTextures->getTextureId(TexturesManager::NUMBERS),
                                  m_nPolygons,
                                  m_nPolygonsPositionAttr,
                                  m_nPolygonsTextureAttr,
                                  m_nPolygonsTransformationAttr,
                                  "000",
                                  false);

    // Label of score two for single
    m_pSingleScoreTwo = new Label(m_pMatrix,
                                  0.41f, 0.97f, LABEL_WIDTH, LABEL_HEIGHT,
                                  m_pTextures->getTextureId(TexturesManager::NUMBERS),
                                  m_nPolygons,
                                  m_nPolygonsPositionAttr,
                                  m_nPolygonsTextureAttr,
                                  m_nPolygonsTransformationAttr,
                                  "000",
                                  false);

    // Label of score one for multi
    m_pMultiScoreOne = new Label(m_pMatrix,
                                 -0.25f, 1.0f, LABEL_WIDTH, LABEL_HEIGHT,
                                 m_pTextures->getTextureId(TexturesManager::NUMBERS),
                                 m_nPolygons,
                                 m_nPolygonsPositionAttr,
                                 m_nPolygonsTextureAttr,
                                 m_nPolygonsTransformationAttr,
                                 "000",
                                 true);

    // Label of score two for multi
    m_pMultiScoreTwo = new Label(m_pMatrix,
                                 -0.25f, -1.0f + LABEL_HEIGHT, LABEL_WIDTH, LABEL_HEIGHT,
                                 m_pTextures->getTextureId(TexturesManager::NUMBERS),
                                 m_nPolygons,
                                 m_nPolygonsPositionAttr,
                                 m_nPolygonsTextureAttr,
                                 m_nPolygonsTransformationAttr,
                                 "000",
                                 false);

    // Field
    m_pField = new Platform(PLATFORMS_SPEED,
                            -1.0f, BORDER_UP + 0.05f, 2.0f, (BORDER_UP + 0.05f) * 2.0f,
                            m_pTextures->getTextureId(TexturesManager::OBJECTS),
                            m_nPolygons,
                            m_nPolygonsPositionAttr,
                            m_nPolygonsTextureAttr,
                            m_nPolygonsTransformationAttr,
                            m_pMatrix->getDefaultVerticesCoords(),
                            m_pMatrix->getDefaultTextureCoord(),
                            m_pMatrix->getDefaultMatrix4x4());

    m_pField->setVisible(false);


    // Player platform
    m_pPlayer = new Platform(PLATFORMS_SPEED,
                             -0.25, -0.45f, PLATFORMS_WIDTH, PLATFORMS_HEIGHT,
                             m_pTextures->getTextureId(TexturesManager::OBJECTS),
                             m_nPolygons,
                             m_nPolygonsPositionAttr,
                             m_nPolygonsTextureAttr,
                             m_nPolygonsTransformationAttr,
                             m_pMatrix->getDefaultVerticesCoords(),
                             Matrix::setTextureCoords(m_pMatrix->getDefaultTextureCoord(), 2, 2, Matrix::ONE),
                             m_pMatrix->getDefaultMatrix4x4());
    // Enemy platform
    m_pEnemy = new Enemy(PLATFORMS_SPEED * 1.4f,
                         -0.25, 0.75f, PLATFORMS_WIDTH, PLATFORMS_HEIGHT,
                         m_pTextures->getTextureId(TexturesManager::OBJECTS),
                         m_nPolygons,
                         m_nPolygonsPositionAttr,
                         m_nPolygonsTextureAttr,
                         m_nPolygonsTransformationAttr,
                         m_pMatrix->getDefaultVerticesCoords(),
                         Matrix::rotateTextureCoord(Matrix::setTextureCoords(m_pMatrix->getDefaultTextureCoord(), 2, 2, Matrix::TWO), 2),
                         m_pMatrix->getDefaultMatrix4x4());

    // Player two
    m_pPlayerTwo = new Platform(PLATFORMS_SPEED,
                                -0.25, 0.45f  + PLATFORMS_HEIGHT, PLATFORMS_WIDTH, PLATFORMS_HEIGHT,
                                m_pTextures->getTextureId(TexturesManager::OBJECTS),
                                m_nPolygons,
                                m_nPolygonsPositionAttr,
                                m_nPolygonsTextureAttr,
                                m_nPolygonsTransformationAttr,
                                m_pMatrix->getDefaultVerticesCoords(),
                                Matrix::rotateTextureCoord(Matrix::setTextureCoords(m_pMatrix->getDefaultTextureCoord(), 2, 2, Matrix::ONE), 2),
                                m_pMatrix->getDefaultMatrix4x4());

    // Enemy platform
    m_pBall = new Ball(BALL_SPEED,
                    0.0 - BALL_WIDTH * 0.5f, 0.0f + m_fBallWidth * 0.5f, BALL_WIDTH, m_fBallWidth,
                       m_pTextures->getTextureId(TexturesManager::OBJECTS),
                       m_nPolygons,
                       m_nPolygonsPositionAttr,
                       m_nPolygonsTextureAttr,
                       m_nPolygonsTransformationAttr,
                       m_pMatrix->getDefaultVerticesCoords(),
                       Matrix::setTextureCoords(m_pMatrix->getDefaultTextureCoord(), 2, 2, Matrix::THREE),
                       m_pMatrix->getDefaultMatrix4x4(),
                       m_pSplash);

    // Menu header
    m_pMenuHeader = new View(m_pTextures->getTextureId(TexturesManager::BUTTONS),
                             m_nPolygons,
                             m_nPolygonsPositionAttr,
                             m_nPolygonsTextureAttr,
                             m_nPolygonsTransformationAttr,
                             Matrix::setVerticesCoords(-0.8f, 0.95f, 1.6f, 0.3f, m_pMatrix->getDefaultVerticesCoords()),
                             Matrix::setTextureCoords(m_pMatrix->getDefaultTextureCoord(), 2, 4, Matrix::EIGHT),
                             m_pMatrix->getDefaultMatrix4x4());

    // Choose single mode
    m_pSingle = new Button(false,
                           true,
                           false,
                           BUTTON_MENU_X_POSITION, 0.6f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::SIX, Matrix::FIFE,
                           m_pTextures->getTextureId(TexturesManager::BUTTONS),
                           m_nPolygons,
                           m_nPolygonsPositionAttr,
                           m_nPolygonsTextureAttr,
                           m_nPolygonsTransformationAttr,
                           m_pMatrix->getDefaultVerticesCoords(),
                           m_pMatrix->getDefaultTextureCoord(),
                           m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pSingle);
    m_oMenuButtons.push_back(m_pSingle);

    // Choose multiplayer mode
    m_pMulti = new Button(false,
                          true,
                          false,
                          BUTTON_MENU_X_POSITION, 0.3f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::EIGHT, Matrix::SEVEN,
                          m_pTextures->getTextureId(TexturesManager::BUTTONS),
                          m_nPolygons,
                          m_nPolygonsPositionAttr,
                          m_nPolygonsTextureAttr,
                          m_nPolygonsTransformationAttr,
                          m_pMatrix->getDefaultVerticesCoords(),
                          m_pMatrix->getDefaultTextureCoord(),
                          m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pMulti);
    m_oMenuButtons.push_back(m_pMulti);

    // Sound off/on
    m_pSound = new Button(true,
                          true,
                          false,
                          BUTTON_MENU_X_POSITION, 0.0f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::TEN, Matrix::NINE,
                          m_pTextures->getTextureId(TexturesManager::BUTTONS),
                          m_nPolygons,
                          m_nPolygonsPositionAttr,
                          m_nPolygonsTextureAttr,
                          m_nPolygonsTransformationAttr,
                          m_pMatrix->getDefaultVerticesCoords(),
                          m_pMatrix->getDefaultTextureCoord(),
                          m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pSound);
    m_oMenuButtons.push_back(m_pSound);

    // Quality
    m_pQuality = new Button(true,
                            true,
                            false,
                            BUTTON_MENU_X_POSITION, -0.3f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::TWELVE, Matrix::ELEVEN,
                            m_pTextures->getTextureId(TexturesManager::BUTTONS),
                            m_nPolygons,
                            m_nPolygonsPositionAttr,
                            m_nPolygonsTextureAttr,
                            m_nPolygonsTransformationAttr,
                            m_pMatrix->getDefaultVerticesCoords(),
                            m_pMatrix->getDefaultTextureCoord(),
                            m_pMatrix->getDefaultMatrix4x4());
    m_pQuality->setState(true);
    m_oButtons.push_back(m_pQuality);
    m_oMenuButtons.push_back(m_pQuality);

    // Exit
    m_pExit = new Button(false,
                         true,
                         false,
                         BUTTON_MENU_X_POSITION, -0.6f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::FOURTEEN, Matrix::THIRTEEN,
                         m_pTextures->getTextureId(TexturesManager::BUTTONS),
                         m_nPolygons,
                         m_nPolygonsPositionAttr,
                         m_nPolygonsTextureAttr,
                         m_nPolygonsTransformationAttr,
                         m_pMatrix->getDefaultVerticesCoords(),
                         m_pMatrix->getDefaultTextureCoord(),
                         m_pMatrix->getDefaultMatrix4x4());
    m_oButtons.push_back(m_pExit);
    m_oMenuButtons.push_back(m_pExit);

    // Set default quality
    highQuality();
}

void Game::destroyTextureObjects() {
    // Particles
    delete m_pParticles;
    delete m_pSplash;
    delete m_pPlume;
    delete m_pShape;

    // Common
    delete m_pBordDown;
    delete m_pMenuHeader;

    delete m_pField;
    delete m_pBall;
    delete m_pLeft;
    delete m_pPlayPause;
    delete m_pRight;

    // For single
    delete m_pSingleSpeed;
    delete m_pSingleScoreOne;
    delete m_pSingleScoreTwo;
    delete m_pBordUp;
    delete m_pPlayer;
    delete m_pPlayerTwo;
    delete m_pEnemy;

    // For multi
    delete m_pMultiScoreOne;
    delete m_pMultiScoreTwo;
    delete m_pLeftTwo;
    delete m_pPlayPauseTwo;
    delete m_pRightTwo;
    delete m_pBordDownTwo;

    // For menu
    delete m_pSingle;
    delete m_pMulti;
    delete m_pSound;
    delete m_pExit;

    m_oButtons.clear();
    m_oMenuButtons.clear();
}

// -------------------------------------------------------------------------------------------------
// BACKGROUND BLOCK
void Game::renderBackground() {
    // Particles
    m_pParticles->render();
}

// -------------------------------------------------------------------------------------------------
// MENU BLOCK
void Game::drawFrameMenu() {
    m_pMenuHeader->render();
    m_pSingle->render();
    m_pMulti->render();
    m_pSound->render();
    m_pQuality->render();
    m_pExit->render();
}

void Game::logicMenu() {
    // Show menu buttons
    //setMenuButtonsVisibility(true);
    m_pExit->setVisible(true);

    // For game mode
    if (m_pSingle->getState()) {
        m_oGameState = State::SINGLE;
        //setMenuButtonsVisibility(false);
        m_pExit->setVisible(false);
    } else if (m_pMulti->getState()) {
        m_oGameState = State::MULTI;
        //setMenuButtonsVisibility(false);
        m_pExit->setVisible(false);
    }

    // For set sound
    m_pOSLSound->setSound(!m_pSound->getState());
    if (m_pOSLSound->isSoundOn()) {
        m_pOSLSound->play(OSLSound::BACKGROUND);
    } else {
        // Without pause - stop after few second...
        m_pOSLSound->pauseStopAll();
    }

    // For quality. Set once after click.
    if (m_pQuality->isClicked()) {
        if (m_pQuality->getState()) {
            highQuality();
        } else {
            lowQuality();
        }
    }
}

void Game::lowQuality() {
    // Background stars
    m_pParticles->setParticlesCount(800);
    m_pParticles->setParticlesSize(4.0f);
    m_pParticles->setSettings();

    // Background shape
    m_pShape->setParticlesCount(7000);
    m_pShape->setParticlesSize(5.0f);
    m_pShape->setSettings();

    // Balls effects
    m_pSplash->setParticlesCount(50);
    m_pSplash->setParticlesSize(3.0f);
    m_pSplash->setSettings();

    m_pPlume->setParticlesCount(70);
    m_pPlume->setParticlesSize(3.0f);
    m_pPlume->setSettings();
}

void Game::highQuality() {
    // Background stars
    m_pParticles->setParticlesCount(3000);
    m_pParticles->setParticlesSize(10.0f);
    m_pParticles->setSettings();

    // Background shape
    m_pShape->setParticlesCount(20000);
    m_pShape->setParticlesSize(8.0f);
    m_pShape->setSettings();

    // Balls effects
    m_pSplash->setParticlesCount(200);
    m_pSplash->setParticlesSize(12.0f);
    m_pSplash->setSettings();

    m_pPlume->setParticlesCount(300);
    m_pPlume->setParticlesSize(10.0f);
    m_pPlume->setSettings();
}

// -------------------------------------------------------------------------------------------------
// SINGLE BLOCK
void Game::drawFrameForSingle() {
    renderSingleObjects();
    renderSingleInterface();
}

void Game::logicSingle() {

    // Check buttons and move for player
    if (m_pLeft->getState() && !m_pPlayer->collision(m_pField)) {
        m_pPlayer->setDx(NEGATIVE * m_pPlayer->getStep());
    } else if (m_pRight->getState() && !m_pPlayer->collision(m_pField)) {
        m_pPlayer->setDx(m_pPlayer->getStep());
    } else {
        m_pPlayer->setDx(STOP_MOVE);
        m_pPlayer->getCrossPoints()->clear();
    }

    // Check collision
    m_pEnemy->collision(m_pBall);
    ((Platform *)m_pEnemy)->collision(m_pField);

    // Play m_pSound  for ball-player collision
    if (m_pBall->collision(m_pPlayer) || m_pBall->collision((Platform *)m_pEnemy)) {
        m_pOSLSound->play(OSLSound::BALL);
    }

    // Set score for players and play sound
    switch(m_pBall->collision(m_pField)) {
        case Object::DOWN:
            m_pPlayer->setScore();
            m_pOSLSound->play(OSLSound::BALL);
            break;
        case Object::UP:
            m_pEnemy->setScore();
            m_pOSLSound->play(OSLSound::BALL);
            break;
    }

    // Check if ball is out of field
    if (m_pBall->getIsOut()) {
        m_pPlayPause->setState(false);
        m_pBall->setIsOut(false);
        m_pOSLSound->play(OSLSound::OUT);

        // Set shape color change
        m_pShape->setColorLight();
        m_pShape->setColorTimer();
        m_pShape->setColorPart(m_pEnemy->getScore(), m_pPlayer->getScore());

        // Players positions
        m_pPlayer->setDefaultPosition();
        m_pEnemy->setDefaultPosition();
    }

    // Label for ball speed
    if (m_pBall->getSpeed() > 0) {
        m_pSingleSpeed->setNumber(Methods::fillLeft(Methods::intToString(m_pBall->getSpeed()), '0', 3));
    }

    // Labels for player scores
    m_pSingleScoreTwo->setNumber(Methods::fillLeft(Methods::intToString((m_pEnemy->getScore())), '0', 3));
    m_pSingleScoreOne->setNumber(Methods::fillLeft(Methods::intToString((m_pPlayer->getScore())), '0', 3));

    // Move ball
    m_pBall->move();

    // Set new position for plume
    m_pPlume->setPlumePoints(m_pBall->getPlumePoints());
}

GLfloat* Game::setBordDownPosition(GLfloat* positionCoords, bool isInverse) {
    GLfloat inverseCoeff = isInverse? -1.0f : 1.0f;
    if (!isInverse) {
        positionCoords[1] = BORDER_DOWN * inverseCoeff;
        positionCoords[7] = BORDER_DOWN * inverseCoeff;
    } else {
        positionCoords[3] = BORDER_DOWN * inverseCoeff;
        positionCoords[5] = BORDER_DOWN * inverseCoeff;
    }

    return positionCoords;
}

GLfloat * Game::setBordUpPosition(GLfloat * positionCoords) {
    positionCoords[3] = BORDER_UP;
    positionCoords[5] = BORDER_UP;
    return positionCoords;
}

void Game::renderSingleInterface() {
    // Bord down
    m_pBordDown->render();

    // Bord up
    m_pBordUp->render();

    // Speed
    m_pSingleSpeed->render();

    // Score one
    m_pSingleScoreOne->render();

    // Score two
    m_pSingleScoreTwo->render();

    // Button left
    m_pLeft->render();

    // Button right
    m_pRight->render();

    // Button playPause
    m_pPlayPause->render();
}

void Game::renderSingleObjects() {
    // Background shape
    m_pShape->render();

    // Plume
    if (m_pPlayPause->getState()) {
        m_pPlume->render();
    }

    // Ball
    m_pBall->render();

    // Player
    m_pPlayer->render();

    // Enemy
    m_pEnemy->render();

    // Splash
    m_pSplash->render();
}

// -------------------------------------------------------------------------------------------------
// MULTI BLOCK
void Game::logicMulti() {

    // Check buttons and move for player one
    if (m_pLeft->getState() && !m_pPlayer->collision(m_pField)) {
        m_pPlayer->setDx(NEGATIVE * m_pPlayer->getStep());
    } else if (m_pRight->getState() && !m_pPlayer->collision(m_pField)) {
        m_pPlayer->setDx(m_pPlayer->getStep());
    } else {
        m_pPlayer->setDx(STOP_MOVE);
        m_pPlayer->getCrossPoints()->clear();
    }

    // Check buttons and move for player two
    if (m_pLeftTwo->getState() && !m_pPlayerTwo->collision(m_pField)) {
        m_pPlayerTwo->setDx(NEGATIVE * m_pPlayerTwo->getStep());
    } else if (m_pRightTwo->getState() && !m_pPlayerTwo->collision(m_pField)) {
        m_pPlayerTwo->setDx(m_pPlayerTwo->getStep());
    } else {
        m_pPlayerTwo->setDx(STOP_MOVE);
        m_pPlayerTwo->getCrossPoints()->clear();
    }

    // Check collision for sound
    if (m_pBall->collision(m_pPlayer) || m_pBall->collision(m_pPlayerTwo)) {
        m_pOSLSound->play(OSLSound::BALL);
    }

    // Set score for players and play sound
    switch (m_pBall->collision(m_pField)) {
        case Object::DOWN:
            m_pPlayer->setScore();
            m_pOSLSound->play(OSLSound::BALL);
            break;
        case Object::UP:
            m_pPlayerTwo->setScore();
            m_pOSLSound->play(OSLSound::BALL);
            break;
    }

    // Check if ball is out of field
    if (m_pBall->getIsOut()) {
        m_pPlayPause->setState(false);
        m_pPlayPauseTwo->setState(false);
        m_pBall->setIsOut(false);
        m_pOSLSound->play(OSLSound::OUT);

        // Set shape color change and colors parts
        m_pShape->setColorLight();
        m_pShape->setColorTimer();
        m_pShape->setColorPart(m_pPlayer->getScore(), m_pPlayerTwo->getScore());

        // Players positions
        m_pPlayer->setDefaultPosition();
        m_pPlayerTwo->setDefaultPosition();
    }

    // Reverse score for player one
    m_pMultiScoreOne->setNumber(Methods::fillLeft(Methods::intToString(m_pPlayer->getScore()), '0', 3));
    m_pMultiScoreTwo->setNumber(Methods::fillLeft(Methods::intToString(m_pPlayerTwo->getScore()), '0', 3));
    m_pBall->move();

    // Set new position for plume
    m_pPlume->setPlumePoints(m_pBall->getPlumePoints());
}

void Game::drawFrameForMulti() {
    renderMultiObjects();
    renderMultiInterface();
}

void Game::renderMultiInterface() {
    // Bord down
    m_pBordDown->render();

    // Bord up
    m_pBordDownTwo->render();

    // Button left
    m_pLeft->render();

    // Button right
    m_pRight->render();

    // Button playPause
    m_pPlayPause->render();

    // Button left
    m_pLeftTwo->render();

    // Button right
    m_pRightTwo->render();

    // Button playPause
    m_pPlayPauseTwo->render();

    // Score one
    m_pMultiScoreOne->render();

    // Score two
    m_pMultiScoreTwo->render();
}

void Game::renderMultiObjects() {
    // Background shape
    m_pShape->render();

    // Plume
    if (m_pPlayPause->getState() && m_pPlayPauseTwo->getState()) {
        m_pPlume->render();
    }

    // Ball
    m_pBall->render();

    // Player
    m_pPlayer->render();

    // Enemy
    m_pPlayerTwo->render();

    // Splash
    m_pSplash->render();
}