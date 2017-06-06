#include "Main.h"

Main::~Main(){
    LOGI("~Main");

    // Sound free
    soundObj->pauseStopAll();
    delete soundObj;

    // Particles
    delete particles;
    delete splashObj;
    delete plumeObj;
    delete shapeObj;

    // Objects
    // Common
    delete matrix;
    delete bordDown;
    delete menuHeader;

    delete field;
    delete ball;
    delete left;
    delete playPause;
    delete right;

    // For single
    delete singleSpeed;
    delete singleScoreOne;
    delete singleScoreTwo;
    delete bordUp;
    delete player;
    delete playerTwo;
    delete enemy;

    // For multi
    delete multiScoreOne;
    delete multiScoreTwo;
    delete leftTwo;
    delete playPauseTwo;
    delete rightTwo;
    delete bordDownTwo;

    // For menu
    delete single;
    delete multi;
    delete sound;
    delete exit;

    // Free textures
    delete textures;
}

bool Main::init() {
    // Polygons
    polygons = MakeShaders::createProgram(MakeShaders::v_main_shader, MakeShaders::f_main_shader);
    if(polygons == 0)
        return false;

    polygonsPositionAttr = glGetAttribLocation(polygons, "a_Position");
    checkGLError("Main::initArrays - polygons - a_Position");
    polygonsTextureAttr = glGetAttribLocation(polygons, "a_Texture");
    checkGLError("Main::initArrays - polygons - a_Texture");
    polygonsTransformationAttr = glGetUniformLocation(polygons, "u_Matrix");
    checkGLError("Main::initArrays - polygons - u_Matrix");

    // Sprites
    sprites = MakeShaders::createProgram(MakeShaders::v_point_shader, MakeShaders::f_point_shader);
    if(sprites == 0)
        return false;

    spritesRandomPosition = glGetAttribLocation(sprites, "a_RandomArrayCoords");
    checkGLError("Main::initArrays - sprites - a_RandomArrayCoords");
    spritesRandomSpeed = glGetAttribLocation(sprites, "a_RandomArraySpeed");
    checkGLError("Main::initArrays - sprites - a_RandomArraySpeed");
    spritesRandomRadius = glGetAttribLocation(sprites, "a_RandomArrayRadius");
    checkGLError("Main::initArrays - sprites - a_RandomArrayRadius");
    spritesDelta = glGetAttribLocation(sprites, "a_Delta");
    checkGLError("Main::initArrays - sprites - a_Delta");
    spritesSize = glGetUniformLocation(sprites, "u_Size");
    checkGLError("Main::initArrays - sprites - u_Size");
    spritesTotalDeltaSpeed = glGetUniformLocation(sprites, "u_TotalDeltaSpeed");
    checkGLError("Main::initArrays - sprites - u_TotalDeltaSpeed");
    spritesColorStart = glGetAttribLocation(sprites, "a_ColorStart");
    checkGLError("Main::initArrays - sprites - a_ColorStart");
    spritesColorEnd = glGetAttribLocation(sprites, "a_ColorEnd");
    checkGLError("Main::initArrays - sprites - a_ColorEnd");

    // Splash
    splash = MakeShaders::createProgram(MakeShaders::v_splash_shader, MakeShaders::f_splash_shader);
    if(splash == 0)
        return false;

    splashPosition = glGetAttribLocation(splash, "a_ArrayCoords");
    checkGLError("Main::initArrays - splash - a_ArrayCoords");
    splashColorStart = glGetAttribLocation(splash, "a_ColorStart");
    checkGLError("Main::initArrays - splash - a_ColorStart");
    splashColorEnd = glGetAttribLocation(splash, "a_ColorEnd");
    checkGLError("Main::initArrays - splash - a_ColorEnd");
    splashDelta = glGetAttribLocation(splash, "a_Delta");
    checkGLError("Main::initArrays - splash - a_Delta");
    splashSize = glGetUniformLocation(splash, "u_Size");
    checkGLError("Main::initArrays - splash - u_Size");

    // Shape
    shape = MakeShaders::createProgram(MakeShaders::v_shape_shader, MakeShaders::f_shape_shader);
    if(shape == 0)
        return false;

    shapeAngle = glGetAttribLocation(shape, "a_ArrayAngle");
    checkGLError("Main::initArrays - shape - a_ArraySpeed");
    shapeColor = glGetAttribLocation(shape, "a_ArrayColor");
    checkGLError("Main::initArrays - shape - a_ArrayColor");
    shapeCenter = glGetUniformLocation(shape, "u_Center");
    checkGLError("Main::initArrays - shape - u_Center");
    shapeRadius = glGetUniformLocation(shape, "u_Radius");
    checkGLError("Main::initArrays - shape - u_Radius");
    shapeArguments = glGetUniformLocation(shape, "u_Arguments");
    checkGLError("Main::initArrays - shape - u_Arguments");
    shapeSize = glGetUniformLocation(shape, "u_PointSize");
    checkGLError("Main::initArrays - shape - u_PointSize");
    shapeTotalDeltaSpeed = glGetUniformLocation(shape, "u_TotalDeltaSpeed");
    checkGLError("Main::initArrays - shape - u_TotalDeltaSpeed");

    // Clear compiliers
    glReleaseShaderCompiler();

    //On alfa-blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkGLError("Main::initArrays - glBlendFunc");
    glEnable(GL_BLEND);
    checkGLError("Main::initArrays - glEnable");

    // Set viewport
    glViewport(0, 0, width, height);
    checkGLError("Main::initArrays - glViewport");

    return true;
}

void Main::createObjects(){

    // Load textures
    textures = new ManageTexture(env, pngManager, assetManager);

    // For work with matrix
    matrix = new Matrix();

    // Background shape
    shapeObj = new Shape(  15000,
                           0.0f,
                           0.0f,
                           0.3f / SCREEN_COEFFICIENT,
                           0.3f,
                           shape,
                           textures->getTexturesPackIDs(ManageTexture::PARTICLES),
                           shapeAngle,
                           shapeColor,
                           shapeCenter,
                           shapeRadius,
                           shapeArguments,
                           shapeSize,
                           shapeTotalDeltaSpeed);

    // Background stars
    particles = new Particles(3000,
                              sprites,
                              textures->getTexturesPackIDs(ManageTexture::PARTICLES),
                              spritesRandomPosition,
                              spritesRandomSpeed,
                              spritesRandomRadius,
                              spritesDelta,
                              spritesColorStart,
                              spritesColorEnd,
                              spritesSize,
                              spritesTotalDeltaSpeed);

    // Splash by collisions
    splashObj = new Splash( 200, 50,
                            splash,
                            textures->getTexturesPackIDs(ManageTexture::SPLASH),
                            splashPosition,
                            splashColorStart,
                            splashColorEnd,
                            splashDelta,
                            splashSize);

    // Plume from ball
    plumeObj = new Plume( 350,
                          splash,
                          textures->getTexturesPackIDs(ManageTexture::PLUME),
                          splashPosition,
                          splashColorStart,
                          splashColorEnd,
                          splashDelta,
                          splashSize);

    // Bord down
    bordDown = new View(textures->getTexturesPackIDs(ManageTexture::BORDERS),
                        polygons,
                        polygonsPositionAttr,
                        polygonsTextureAttr,
                        polygonsTransformationAttr,
                        setBordDownPosition(matrix->getDefaultVerticesCoords(), false),
                        Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 1, 2, Matrix::TWO),
                        matrix->getDefaultMatrix4x4());

    // Bord down for player two
    bordDownTwo = new View(textures->getTexturesPackIDs(ManageTexture::BORDERS),
                            polygons,
                            polygonsPositionAttr,
                            polygonsTextureAttr,
                            polygonsTransformationAttr,
                            setBordDownPosition(matrix->getDefaultVerticesCoords(), true),
                            Matrix::rotateTextureCoord(Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 1, 2, Matrix::TWO), 2),
                            matrix->getDefaultMatrix4x4());

    // Bord up
    bordUp = new View(textures->getTexturesPackIDs(ManageTexture::BORDERS),
                        polygons,
                        polygonsPositionAttr,
                        polygonsTextureAttr,
                        polygonsTransformationAttr,
                        setBordUpPosition(matrix->getDefaultVerticesCoords()),
                        Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 1, 2, Matrix::ONE),
                        matrix->getDefaultMatrix4x4());

    // Left button
    left = new Button(false,
                      true,
                      false,
                      -0.88f, -0.76f, BUTTON_CONTROL_HEIGHT / SCREEN_COEFFICIENT, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
                      textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                      polygons,
                      polygonsPositionAttr,
                      polygonsTextureAttr,
                      polygonsTransformationAttr,
                      matrix->getDefaultVerticesCoords(),
                      matrix->getDefaultTextureCoord(),
                      matrix->getDefaultMatrix4x4());
    allButtons.push_back(left);

    // Right button
    right = new Button(false,
                       true,
                       false,
                       0.52f, -0.76f, BUTTON_CONTROL_HEIGHT / SCREEN_COEFFICIENT, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
                       textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                       polygons,
                       polygonsPositionAttr,
                       polygonsTextureAttr,
                       polygonsTransformationAttr,
                       matrix->getDefaultVerticesCoords(),
                       matrix->getDefaultTextureCoord(),
                       matrix->getDefaultMatrix4x4());
    allButtons.push_back(right);

    // Play pause button
    playPause = new Button(true,
                           false,
                           false,
                           -0.25f, -0.72f, BUTTON_START_WIDTH, BUTTON_START_HEIGHT, 4, 4, Matrix::FOUR, Matrix::THREE,
                           textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                           polygons,
                           polygonsPositionAttr,
                           polygonsTextureAttr,
                           polygonsTransformationAttr,
                           matrix->getDefaultVerticesCoords(),
                           matrix->getDefaultTextureCoord(),
                           matrix->getDefaultMatrix4x4());
    allButtons.push_back(playPause);

    // Left button player two
    leftTwo = new Button(false,
                          true,
                          true,
                         -0.88f, 0.76f + BUTTON_CONTROL_HEIGHT, BUTTON_CONTROL_HEIGHT / SCREEN_COEFFICIENT, BUTTON_CONTROL_HEIGHT,  4, 4, Matrix::TWO, Matrix::ONE,
                          textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                          polygons,
                          polygonsPositionAttr,
                          polygonsTextureAttr,
                          polygonsTransformationAttr,
                          matrix->getDefaultVerticesCoords(),
                          matrix->getDefaultTextureCoord(),
                          matrix->getDefaultMatrix4x4());
    allButtons.push_back(leftTwo);

    // Right button player two
    rightTwo = new Button(false,
                           true,
                           true,
                           0.52f, 0.76f + BUTTON_CONTROL_HEIGHT, BUTTON_CONTROL_HEIGHT / SCREEN_COEFFICIENT, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
                           textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                           polygons,
                           polygonsPositionAttr,
                           polygonsTextureAttr,
                           polygonsTransformationAttr,
                           matrix->getDefaultVerticesCoords(),
                           matrix->getDefaultTextureCoord(),
                           matrix->getDefaultMatrix4x4());
    allButtons.push_back(rightTwo);

    // Play pause button player two
    playPauseTwo = new Button(true,
                               false,
                               true,
                               -0.25f, 0.72f + BUTTON_START_HEIGHT, BUTTON_START_WIDTH, BUTTON_START_HEIGHT, 4, 4, Matrix::FOUR, Matrix::THREE,
                               textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                               polygons,
                               polygonsPositionAttr,
                               polygonsTextureAttr,
                               polygonsTransformationAttr,
                               matrix->getDefaultVerticesCoords(),
                               matrix->getDefaultTextureCoord(),
                               matrix->getDefaultMatrix4x4());
    allButtons.push_back(playPauseTwo);

    // Label of singleSpeed
    singleSpeed = new Label(matrix,
                            -0.25f, 0.97f, LABEL_WIDTH, LABEL_HEIGHT,
                            textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                            polygons,
                            polygonsPositionAttr,
                            polygonsTextureAttr,
                            polygonsTransformationAttr,
                            "000",
                            false);

    // Label of score one for single
    singleScoreOne = new Label(matrix,
                               -0.91f, 0.97f, LABEL_WIDTH, LABEL_HEIGHT,
                               textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                               polygons,
                               polygonsPositionAttr,
                               polygonsTextureAttr,
                               polygonsTransformationAttr,
                               "000",
                               false);

    // Label of score two for single
    singleScoreTwo = new Label(matrix,
                               0.41f, 0.97f, LABEL_WIDTH, LABEL_HEIGHT,
                               textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                               polygons,
                               polygonsPositionAttr,
                               polygonsTextureAttr,
                               polygonsTransformationAttr,
                               "000",
                               false);

    // Label of score one for multi
    multiScoreOne = new Label(matrix,
                               -0.25f, 1.0f, LABEL_WIDTH, LABEL_HEIGHT,
                               textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                               polygons,
                               polygonsPositionAttr,
                               polygonsTextureAttr,
                               polygonsTransformationAttr,
                               "000",
                               true);

    // Label of score two for multi
    multiScoreTwo = new Label(matrix,
                               -0.25f, -1.0f + LABEL_HEIGHT, LABEL_WIDTH, LABEL_HEIGHT,
                               textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                               polygons,
                               polygonsPositionAttr,
                               polygonsTextureAttr,
                               polygonsTransformationAttr,
                               "000",
                               false);

    // Field
    field = new Platform( PLATFORMS_SPEED,
                           -1.0f, BORDER_UP + 0.05f, 2.0f, (BORDER_UP + 0.05f) * 2.0f,
                           textures->getTexturesPackIDs(ManageTexture::OBJECTS),
                           polygons,
                           polygonsPositionAttr,
                           polygonsTextureAttr,
                           polygonsTransformationAttr,
                           matrix->getDefaultVerticesCoords(),
                           matrix->getDefaultTextureCoord(),
                           matrix->getDefaultMatrix4x4());

    field->setVisible(false);


    // Player platform
    player = new Platform( PLATFORMS_SPEED,
                           -0.25, -0.45f, PLATFORMS_WIDTH, PLATFORMS_HEIGHT,
                           textures->getTexturesPackIDs(ManageTexture::OBJECTS),
                           polygons,
                           polygonsPositionAttr,
                           polygonsTextureAttr,
                           polygonsTransformationAttr,
                           matrix->getDefaultVerticesCoords(),
                           Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::ONE),
                           matrix->getDefaultMatrix4x4());
    // Enemy platform
    enemy = new Enemy( PLATFORMS_SPEED * 1.4f,
                       -0.25, 0.75f, PLATFORMS_WIDTH, PLATFORMS_HEIGHT,
                       textures->getTexturesPackIDs(ManageTexture::OBJECTS),
                       polygons,
                       polygonsPositionAttr,
                       polygonsTextureAttr,
                       polygonsTransformationAttr,
                       matrix->getDefaultVerticesCoords(),
                       Matrix::rotateTextureCoord(Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::TWO), 2),
                       matrix->getDefaultMatrix4x4());

    // Player two
    playerTwo = new Platform( PLATFORMS_SPEED,
                               -0.25, 0.45f  + PLATFORMS_HEIGHT, PLATFORMS_WIDTH, PLATFORMS_HEIGHT,
                               textures->getTexturesPackIDs(ManageTexture::OBJECTS),
                               polygons,
                               polygonsPositionAttr,
                               polygonsTextureAttr,
                               polygonsTransformationAttr,
                               matrix->getDefaultVerticesCoords(),
                               Matrix::rotateTextureCoord(Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::ONE), 2),
                               matrix->getDefaultMatrix4x4());

    // Enemy platform
    ball = new Ball( BALL_SPEED,
                    0.0 - BALL_WIDTH * 0.5f, 0.0f + BALL_HEIGHT * 0.5f, BALL_WIDTH, BALL_HEIGHT,
                    textures->getTexturesPackIDs(ManageTexture::OBJECTS),
                    polygons,
                    polygonsPositionAttr,
                    polygonsTextureAttr,
                    polygonsTransformationAttr,
                    matrix->getDefaultVerticesCoords(),
                    Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::THREE),
                    matrix->getDefaultMatrix4x4(),
                    splashObj);

    // Menu header
    menuHeader = new View(textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                          polygons,
                          polygonsPositionAttr,
                          polygonsTextureAttr,
                          polygonsTransformationAttr,
                          Matrix::setVerticesCoords(-0.8f, 0.95f, 1.6f, 0.3f, matrix->getDefaultVerticesCoords()),
                          Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 4, Matrix::EIGHT),
                          matrix->getDefaultMatrix4x4());

    // Choose single mode
    single = new Button(false,
                          true,
                          false,
                          BUTTON_MENU_X_POSITION, 0.6f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT,  4, 4, Matrix::SIX, Matrix::FIFE,
                          textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                          polygons,
                          polygonsPositionAttr,
                          polygonsTextureAttr,
                          polygonsTransformationAttr,
                          matrix->getDefaultVerticesCoords(),
                          matrix->getDefaultTextureCoord(),
                          matrix->getDefaultMatrix4x4());
    allButtons.push_back(single);
    menuButtons.push_back(single);

    // Choose multiplayer mode
    multi = new Button(false,
                          true,
                          false,
                          BUTTON_MENU_X_POSITION, 0.3f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::EIGHT, Matrix::SEVEN,
                          textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                          polygons,
                          polygonsPositionAttr,
                          polygonsTextureAttr,
                          polygonsTransformationAttr,
                          matrix->getDefaultVerticesCoords(),
                          matrix->getDefaultTextureCoord(),
                          matrix->getDefaultMatrix4x4());
    allButtons.push_back(multi);
    menuButtons.push_back(multi);

    // Sound off/on
    sound = new Button(true,
                       true,
                       false,
                       BUTTON_MENU_X_POSITION, 0.0f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::TEN, Matrix::NINE,
                       textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                       polygons,
                       polygonsPositionAttr,
                       polygonsTextureAttr,
                       polygonsTransformationAttr,
                       matrix->getDefaultVerticesCoords(),
                       matrix->getDefaultTextureCoord(),
                       matrix->getDefaultMatrix4x4());
    allButtons.push_back(sound);
    menuButtons.push_back(sound);

    // Quality
    quality = new Button(true,
                         true,
                         false,
                         BUTTON_MENU_X_POSITION, -0.3f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::TWELVE, Matrix::ELEVEN,
                         textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                         polygons,
                         polygonsPositionAttr,
                         polygonsTextureAttr,
                         polygonsTransformationAttr,
                         matrix->getDefaultVerticesCoords(),
                         matrix->getDefaultTextureCoord(),
                         matrix->getDefaultMatrix4x4());
    allButtons.push_back(quality);
    menuButtons.push_back(quality);

    // Exit
    exit = new Button( false,
                       true,
                       false,
                       BUTTON_MENU_X_POSITION, -0.6f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::FOURTEEN, Matrix::THIRTEEN,
                       textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                       polygons,
                       polygonsPositionAttr,
                       polygonsTextureAttr,
                       polygonsTransformationAttr,
                       matrix->getDefaultVerticesCoords(),
                       matrix->getDefaultTextureCoord(),
                       matrix->getDefaultMatrix4x4());
    allButtons.push_back(exit);
    menuButtons.push_back(exit);

    // Sound
    soundObj = new OSLSound(env, assetManager, false);
    soundObj->play(OSLSound::BACKGROUND);

    // Set default quality
    lowQuality();
}

void Main::setMenuButtonsVisibility(bool isVisible){
    for(int i = 0; i < menuButtons.size(); i++){
        menuButtons[i]->setVisible(isVisible);
    }
}

void Main::step(){
    // Clear screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    checkGLError("Main::step - glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGLError("Main::step - glClear");

    // Draw background everywhere
    renderBackground();

    // Main state of application
    switch(gameState){
        case State::MENU:
            logicMenu();
            // Draw
            drawFrameMenu();
            break;

        case State::SINGLE:
            // Logic
            if(playPause->getState())
                logicSingle();

            // Draw
            drawFrameForSingle();
            break;

        case State::MULTI:
            // Logic
            if(playPause->getState() && playPauseTwo->getState())
                logicMulti();

            // Draw
            drawFrameForMulti();
            break;
    }
}

void Main::setDefault(){
    // Reset splash
    splashObj->resetTimer();

    // Set background shape
    shapeObj->setSettings();

    // PLayers buttons
    playPause->setState(false);
    playPauseTwo->setState(false);

    // Score labels
    player->clearScore();
    playerTwo->clearScore();
    enemy->clearScore();

    // Players positions
    player->setDefaultPosition();
    playerTwo->setDefaultPosition();
    enemy->setDefaultPosition();

    // Balls positions
    ball->setIsOut(false);
    ball->setDefaultPosition();
    ball->resetSpeed();

    // Change labels values
    singleSpeed->setNumber(Methods::fillLeft(Methods::intToString(0), '0', 3));
    singleScoreOne->setNumber(Methods::fillLeft(Methods::intToString((0)), '0', 3));
    singleScoreOne->setNumber(Methods::fillLeft(Methods::intToString((0)), '0', 3));
    multiScoreOne->setNumber(Methods::fillLeft(Methods::intToString(0), '0', 3));
    multiScoreTwo->setNumber(Methods::fillLeft(Methods::intToString(0), '0', 3));
}

// -------------------------------------------------------------------------------------------------
// BACKGROUND BLOCK
void Main::renderBackground(){
    // Particles
    particles->render();
}

// -------------------------------------------------------------------------------------------------
// MENU BLOCK
void Main::drawFrameMenu(){
    menuHeader->render();
    single->render();
    multi->render();
    sound->render();
    quality->render();
    exit->render();
}

void Main::logicMenu(){
    // Show menu buttons
    //setMenuButtonsVisibility(true);
    exit->setVisible(true);

    // For game mode
    if(single->getState()){
        gameState = State::SINGLE;
        //setMenuButtonsVisibility(false);
        exit->setVisible(false);
    } else if(multi->getState()){
        gameState = State::MULTI;
        //setMenuButtonsVisibility(false);
        exit->setVisible(false);
    }

    // For set sound
    soundObj->setSound(!sound->getState());
    if(soundObj->getSound()){
        soundObj->play(OSLSound::BACKGROUND);
    } else {
        // Without pause - stop after few second...
        soundObj->pauseStopAll();
    }

    // For quality. Set once after click.
    if(quality->isClicked()){
        if(quality->getState()){
            highQuality();
        } else {
            lowQuality();
        }
    }
}

void Main::lowQuality(){
    // Background stars
    particles->setParticlesCount(800);
    particles->setParticlesSize(4.0f);
    particles->setSettings();

    // Background shape
    shapeObj->setParticlesCount(7000);
    shapeObj->setParticlesSize(5.0f);
    shapeObj->setSettings();

    // Balls effects
    splashObj->setParticlesCount(50);
    splashObj->setParticlesSize(3.0f);
    splashObj->setSettings();

    plumeObj->setParticlesCount(70);
    plumeObj->setParticlesSize(3.0f);
    plumeObj->setSettings();
}

void Main::highQuality(){
    // Background stars
    particles->setParticlesCount(3000);
    particles->setParticlesSize(10.0f);
    particles->setSettings();

    // Background shape
    shapeObj->setParticlesCount(20000);
    shapeObj->setParticlesSize(8.0f);
    shapeObj->setSettings();

    // Balls effects
    splashObj->setParticlesCount(200);
    splashObj->setParticlesSize(12.0f);
    splashObj->setSettings();

    plumeObj->setParticlesCount(300);
    plumeObj->setParticlesSize(10.0f);
    plumeObj->setSettings();
}

// -------------------------------------------------------------------------------------------------
// BACK BLOCK
bool Main::backAction(){
    if(gameState == State::SINGLE || gameState == State::MULTI){
        setDefault();
        gameState = State::MENU;
        return false;
    } else if(gameState == State::MENU){
        return true;
    }
}

// -------------------------------------------------------------------------------------------------
// SINGLE BLOCK
void Main::drawFrameForSingle(){
    renderSingleObjects();
    renderSingleInterface();
}

void Main::logicSingle(){

    // Check buttons and move for player
    if(left->getState() && !player->collision(field)){
        player->setDx(NEGATIVE * player->getStep());
    } else if(right->getState() && !player->collision(field)){
        player->setDx(player->getStep());
    } else {
        player->setDx(STOP_MOVE);
        player->getCrossPoints()->clear();
    }

    // Check collision
    enemy->collision(ball);
    ((Platform *)enemy)->collision(field);

    // Play sound  for ball-player collision
    if(ball->collision(player) || ball->collision((Platform *)enemy))
        soundObj->play(OSLSound::BALL);

    // Set score for players and play sound
    switch(ball->collision(field)){
        case Object::DOWN:
            player->setScore();
            soundObj->play(OSLSound::BALL);
            break;
        case Object::UP:
            enemy->setScore();
            soundObj->play(OSLSound::BALL);
            break;
    }

    // Check if ball is out of field
    if(ball->getIsOut()){
        playPause->setState(false);
        ball->setIsOut(false);
        soundObj->play(OSLSound::OUT);

        // Set shape color change
        shapeObj->setColorLight();
        shapeObj->setColorTimer();
        shapeObj->setColorPart(enemy->getScore(), player->getScore());

        // Players positions
        player->setDefaultPosition();
        enemy->setDefaultPosition();
    }

    // Label for ball speed
    if(ball->getSpeed() > 0)
        singleSpeed->setNumber(Methods::fillLeft(Methods::intToString(ball->getSpeed()), '0', 3));


    // Labels for player scores
    singleScoreTwo->setNumber(Methods::fillLeft(Methods::intToString((enemy->getScore())), '0', 3));
    singleScoreOne->setNumber(Methods::fillLeft(Methods::intToString((player->getScore())), '0', 3));

    // Move ball
    ball->move();

    // Set new position for plume
    plumeObj->setPlumePoints(ball->getPlumePoints());
}

GLfloat * Main::setBordDownPosition(GLfloat * positionCoords, bool isInverse){
    GLfloat inverseCoeff = isInverse? -1.0f : 1.0f;
    if(!isInverse){
        positionCoords[1] = BORDER_DOWN * inverseCoeff;
        positionCoords[7] = BORDER_DOWN * inverseCoeff;
    } else {
            positionCoords[3] = BORDER_DOWN * inverseCoeff;
            positionCoords[5] = BORDER_DOWN * inverseCoeff;
        }

    return positionCoords;
}

GLfloat * Main::setBordUpPosition(GLfloat * positionCoords){
    positionCoords[3] = BORDER_UP;
    positionCoords[5] = BORDER_UP;
    return positionCoords;
}

void Main::renderSingleInterface(){
    // Bord down
    bordDown->render();

    // Bord up
    bordUp->render();

    // Speed
    singleSpeed->render();

    // Score one
    singleScoreOne->render();

    // Score two
    singleScoreTwo->render();

    // Button left
    left->render();

    // Button right
    right->render();

    // Button playPause
    playPause->render();
}

void Main::renderSingleObjects(){
    // Background shape
    shapeObj->render();

    // Plume
    if(playPause->getState())
        plumeObj->render();

    // Ball
    ball->render();

    // Player
    player->render();

    // Enemy
    enemy->render();

    // Splash
    splashObj->render();
}

// -------------------------------------------------------------------------------------------------
// MULTI BLOCK
void Main::logicMulti(){

    // Check buttons and move for player one
    if(left->getState() && !player->collision(field)){
        player->setDx(NEGATIVE * player->getStep());
    } else if(right->getState() && !player->collision(field)){
        player->setDx(player->getStep());
    } else {
        player->setDx(STOP_MOVE);
        player->getCrossPoints()->clear();
    }

    // Check buttons and move for player two
    if(leftTwo->getState() && !playerTwo->collision(field)){
        playerTwo->setDx(NEGATIVE * playerTwo->getStep());
    } else if(rightTwo->getState() && !playerTwo->collision(field)){
        playerTwo->setDx(playerTwo->getStep());
    } else {
        playerTwo->setDx(STOP_MOVE);
        playerTwo->getCrossPoints()->clear();
    }

    // Check collision for sound
    if(ball->collision(player) || ball->collision(playerTwo))
        soundObj->play(OSLSound::BALL);

    // Set score for players and play sound
    switch(ball->collision(field)){
        case Object::DOWN:
            player->setScore();
            soundObj->play(OSLSound::BALL);
            break;
        case Object::UP:
            playerTwo->setScore();
            soundObj->play(OSLSound::BALL);
            break;
    }

    // Check if ball is out of field
    if(ball->getIsOut()){
        playPause->setState(false);
        playPauseTwo->setState(false);
        ball->setIsOut(false);
        soundObj->play(OSLSound::OUT);

        // Set shape color change and colors parts
        shapeObj->setColorLight();
        shapeObj->setColorTimer();
        shapeObj->setColorPart(player->getScore(), playerTwo->getScore());

        // Players positions
        player->setDefaultPosition();
        playerTwo->setDefaultPosition();
    }

    // Reverse score for player one
    multiScoreOne->setNumber(Methods::fillLeft(Methods::intToString(player->getScore()), '0', 3));
    multiScoreTwo->setNumber(Methods::fillLeft(Methods::intToString(playerTwo->getScore()), '0', 3));
    ball->move();

    // Set new position for plume
    plumeObj->setPlumePoints(ball->getPlumePoints());
}

void Main::drawFrameForMulti(){
    renderMultiObjects();
    renderMultiInterface();
}

void Main::renderMultiInterface(){
    // Bord down
    bordDown->render();

    // Bord up
    bordDownTwo->render();

    // Button left
    left->render();

    // Button right
    right->render();

    // Button playPause
    playPause->render();

    // Button left
    leftTwo->render();

    // Button right
    rightTwo->render();

    // Button playPause
    playPauseTwo->render();

    // Score one
    multiScoreOne->render();

    // Score two
    multiScoreTwo->render();
}

void Main::renderMultiObjects(){
    // Background shape
    shapeObj->render();

    // Plume
    if(playPause->getState() && playPauseTwo->getState())
        plumeObj->render();

    // Ball
    ball->render();

    // Player
    player->render();

    // Enemy
    playerTwo->render();

    // Splash
    splashObj->render();
}