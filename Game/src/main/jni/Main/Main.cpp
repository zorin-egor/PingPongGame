#include "Main.h"

void Main::init() {
    // Polygons
    polygons = MakeShaders::createProgram(MakeShaders::v_main_shader, MakeShaders::f_main_shader);
    polygonsPositionAttr = glGetAttribLocation(polygons, "a_Position");
    checkGLError("Main::init - polygons - a_Position");
    polygonsTextureAttr = glGetAttribLocation(polygons, "a_Texture");
    checkGLError("Main::init - polygons - a_Texture");
    polygonsTransformationAttr = glGetUniformLocation(polygons, "u_Matrix");
    checkGLError("Main::init - polygons - u_Matrix");

    // Sprites
    sprites = MakeShaders::createProgram(MakeShaders::v_point_shader, MakeShaders::f_point_shader);
    spritesRandomPosition = glGetAttribLocation(sprites, "a_RandomArrayCoords");
    checkGLError("Main::init - sprites - a_RandomArrayCoords");
    spritesRandomSpeed = glGetAttribLocation(sprites, "a_RandomArraySpeed");
    checkGLError("Main::init - sprites - a_RandomArraySpeed");
    spritesRandomRadius = glGetAttribLocation(sprites, "a_RandomArrayRadius");
    checkGLError("Main::init - sprites - a_RandomArrayRadius");
    spritesDelta = glGetAttribLocation(sprites, "a_Delta");
    checkGLError("Main::init - sprites - a_Delta");
    spritesSize = glGetUniformLocation(sprites, "u_Size");
    checkGLError("Main::init - sprites - u_Size");
    spritesTotalDeltaSpeed = glGetUniformLocation(sprites, "u_TotalDeltaSpeed");
    checkGLError("Main::init - sprites - u_TotalDeltaSpeed");
    spritesColorStart = glGetAttribLocation(sprites, "a_ColorStart");
    checkGLError("Main::init - sprites - a_ColorStart");
    spritesColorEnd = glGetAttribLocation(sprites, "a_ColorEnd");
    checkGLError("Main::init - sprites - a_ColorEnd");

    // Splash
    splash = MakeShaders::createProgram(MakeShaders::v_splash_shader, MakeShaders::f_splash_shader);
    splashPosition = glGetAttribLocation(splash, "a_ArrayCoords");
    checkGLError("Main::init - splash - a_ArrayCoords");
    splashColorStart = glGetAttribLocation(splash, "a_ColorStart");
    checkGLError("Main::init - splash - a_ColorStart");
    splashColorEnd = glGetAttribLocation(splash, "a_ColorEnd");
    checkGLError("Main::init - splash - a_ColorEnd");
    splashDelta = glGetAttribLocation(splash, "a_Delta");
    checkGLError("Main::init - splash - a_Delta");
    splashSize = glGetUniformLocation(splash, "u_Size");
    checkGLError("Main::init - splash - u_Size");

    //On alfa-blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkGLError("Main::init - glBlendFunc");
    glEnable(GL_BLEND);
    checkGLError("Main::init - glEnable");

    // Set viewport
    glViewport(0, 0, width, height);
    checkGLError("Main::init - glViewport");
}

void Main::createObjects(){

    matrix = new Matrix();
    textures = new ManageTexture(env, pngManager, assetManager);

    // Background stars
    particles = new Particles(1000,
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
    splashObj = new Splash( 100, 50,
                            splash,
                            textures->getTexturesPackIDs(ManageTexture::SPLASH),
                            splashPosition,
                            splashColorStart,
                            splashColorEnd,
                            splashDelta,
                            splashSize);

    // Plume from ball
    plumeObj = new Plume( 300,
                          splash,
                          textures->getTexturesPackIDs(ManageTexture::PLUME),
                          splashPosition,
                          splashColorStart,
                          splashColorEnd,
                          splashDelta,
                          splashSize);

    // Background image
    background = new View(textures->getTexturesPackIDs(ManageTexture::BACKGROUND),
                          polygons,
                          polygonsPositionAttr,
                          polygonsTextureAttr,
                          polygonsTransformationAttr,
                          matrix->getDefaultVerticesCoords(),
                          matrix->getDefaultTextureCoord(),
                          matrix->getDefaultMatrix4x4());

    // Background center image
    center = new View(textures->getTexturesPackIDs(ManageTexture::BACKGROUND_CENTER),
                      polygons,
                      polygonsPositionAttr,
                      polygonsTextureAttr,
                      polygonsTransformationAttr,
                      matrix->getDefaultVerticesCoords(),
                      matrix->getDefaultTextureCoord(),
                      matrix->getDefaultMatrix4x4());

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
                      -0.91f, -0.73f, BUTTON_CONTROL_HEIGHT / SCREEN_COEFFICIENT, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
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
                       0.60f, -0.73f, BUTTON_CONTROL_HEIGHT / SCREEN_COEFFICIENT, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
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
                           -0.24f, -0.65f, BUTTON_START_WIDTH, BUTTON_START_HEIGHT, 4, 4, Matrix::ONE, Matrix::THREE,
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
                         -0.93f, 0.72f + BUTTON_CONTROL_HEIGHT, BUTTON_CONTROL_HEIGHT / SCREEN_COEFFICIENT, BUTTON_CONTROL_HEIGHT,  4, 4, Matrix::TWO, Matrix::ONE,
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
                           0.58f, 0.72f + BUTTON_CONTROL_HEIGHT, BUTTON_CONTROL_HEIGHT / SCREEN_COEFFICIENT, BUTTON_CONTROL_HEIGHT, 4, 4, Matrix::TWO, Matrix::ONE,
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
                               -0.26f, 0.65f + BUTTON_START_HEIGHT, BUTTON_START_WIDTH, BUTTON_START_HEIGHT, 4, 4, Matrix::ONE, Matrix::THREE,
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
                            -0.23f, 0.98f, LABEL_WIDTH, LABEL_HEIGHT,
                            textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                            polygons,
                            polygonsPositionAttr,
                            polygonsTextureAttr,
                            polygonsTransformationAttr,
                            "000",
                            false);

    // Label of score one for single
    singleScoreOne = new Label(matrix,
                               -0.93f, 0.98f, LABEL_WIDTH, LABEL_HEIGHT,
                               textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                               polygons,
                               polygonsPositionAttr,
                               polygonsTextureAttr,
                               polygonsTransformationAttr,
                               "000",
                               false);

    // Label of score two for single
    singleScoreTwo = new Label(matrix,
                               0.43f, 0.98f, LABEL_WIDTH, LABEL_HEIGHT,
                               textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                               polygons,
                               polygonsPositionAttr,
                               polygonsTextureAttr,
                               polygonsTransformationAttr,
                               "000",
                               false);

    // Label of score one for multi
    multiScoreOne = new Label(matrix,
                               -0.27f, 0.8f, LABEL_WIDTH, LABEL_HEIGHT,
                               textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                               polygons,
                               polygonsPositionAttr,
                               polygonsTextureAttr,
                               polygonsTransformationAttr,
                               "000",
                               true);

    // Label of score two for multi
    multiScoreTwo = new Label(matrix,
                               -0.23f, -0.8f + LABEL_HEIGHT, LABEL_WIDTH, LABEL_HEIGHT,
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
                           -0.25, -0.4f, PLATFORMS_WIDTH, PLATFORMS_HEIGHT,
                           textures->getTexturesPackIDs(ManageTexture::OBJECTS),
                           polygons,
                           polygonsPositionAttr,
                           polygonsTextureAttr,
                           polygonsTransformationAttr,
                           matrix->getDefaultVerticesCoords(),
                           Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::ONE),
                           matrix->getDefaultMatrix4x4());
    // Enemy platform
    enemy = new Enemy( PLATFORMS_SPEED,
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
                               -0.25, 0.4f  + PLATFORMS_HEIGHT, PLATFORMS_WIDTH, PLATFORMS_HEIGHT,
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
                    0.0, 0.0f, BALL_WIDTH, BALL_HEIGHT,
                    textures->getTexturesPackIDs(ManageTexture::OBJECTS),
                    polygons,
                    polygonsPositionAttr,
                    polygonsTextureAttr,
                    polygonsTransformationAttr,
                    matrix->getDefaultVerticesCoords(),
                    Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::FOUR),
                    matrix->getDefaultMatrix4x4(),
                    splashObj);

    // Menu header
    menuHeader = new View(textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                          polygons,
                          polygonsPositionAttr,
                          polygonsTextureAttr,
                          polygonsTransformationAttr,
                          Matrix::setVerticesCoords(-0.8f, 0.95f, 1.6f, 0.3f, matrix->getDefaultVerticesCoords()),
                          Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 4, Matrix::SEVEN),
                          matrix->getDefaultMatrix4x4());

    // Choose single mode
    single = new Button(false,
                          true,
                          -0.8f, 0.7f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT,  4, 4, Matrix::FIFE, Matrix::FOUR,
                          textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                          polygons,
                          polygonsPositionAttr,
                          polygonsTextureAttr,
                          polygonsTransformationAttr,
                          matrix->getDefaultVerticesCoords(),
                          matrix->getDefaultTextureCoord(),
                          matrix->getDefaultMatrix4x4());
    allButtons.push_back(single);

    // Choose multiplayer mode
    multi = new Button(false,
                          true,
                          -0.8f, 0.3f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::SEVEN, Matrix::SIX,
                          textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                          polygons,
                          polygonsPositionAttr,
                          polygonsTextureAttr,
                          polygonsTransformationAttr,
                          matrix->getDefaultVerticesCoords(),
                          matrix->getDefaultTextureCoord(),
                          matrix->getDefaultMatrix4x4());
    allButtons.push_back(multi);

    // Sound off/on
    sound = new Button(true,
                       true,
                       -0.8f, -0.1f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::NINE, Matrix::EIGHT,
                       textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                       polygons,
                       polygonsPositionAttr,
                       polygonsTextureAttr,
                       polygonsTransformationAttr,
                       matrix->getDefaultVerticesCoords(),
                       matrix->getDefaultTextureCoord(),
                       matrix->getDefaultMatrix4x4());
    allButtons.push_back(sound);

    // Exit
    exit = new Button(false,
                       true,
                       -0.8f, -0.5f, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT, 4, 4, Matrix::ELEVEN, Matrix::TEN,
                       textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                       polygons,
                       polygonsPositionAttr,
                       polygonsTextureAttr,
                       polygonsTransformationAttr,
                       matrix->getDefaultVerticesCoords(),
                       matrix->getDefaultTextureCoord(),
                       matrix->getDefaultMatrix4x4());
    allButtons.push_back(exit);

    // Sound
    soundObj = new OSLSound(env, assetManager, true);
    soundObj->play(OSLSound::BACKGROUND);
}

void Main::step(){
    // Clear screen
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    checkGLError("Main::step - glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGLError("Main::step - glClear");

    // Draw background everywhere
    renderBackground();

    // Main state of application
    switch(gameState){
        case State::MENU:
            Main::logicMenu();
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
    playPause->setState(false);
    playPauseTwo->setState(false);

    player->clearScore();
    playerTwo->clearScore();
    enemy->clearScore();

    player->setDefaultPosition();
    playerTwo->setDefaultPosition();
    enemy->setDefaultPosition();

    ball->setIsOut(false);
    ball->setDefaultPosition();
    ball->resetSpeed();

    singleSpeed->setNumber(Methods::fillLeft(Methods::intToString(0), '0', 3));
    singleScoreOne->setNumber(Methods::fillLeft(Methods::intToString((0)), '0', 3));
    singleScoreOne->setNumber(Methods::fillLeft(Methods::intToString((0)), '0', 3));
    multiScoreOne->setNumber(Methods::fillLeft(Methods::intToString(0), '0', 3));
    multiScoreTwo->setNumber(Methods::fillLeft(Methods::intToString(0), '0', 3));
}

// -------------------------------------------------------------------------------------------------
// BACKGROUND BLOCK

void Main::renderBackground(){
    // Background
    background->render();

    // Rotate background
    rotateBackground();

    // Particles
    particles->render();
}

void Main::rotateBackground(){
    if(deltaRotate >= CENTER_ROTATE)
        deltaRotate = NEGATIVE * CENTER_ROTATE;

    center->setTransformationMatrix(Matrix::setRotateMatrix4x4(Matrix::setRotateMatrix4x4(center->getTransformationMatrix(), deltaRotate += CENTER_SPEED, Matrix::X), deltaRotate, Matrix::Z));
    center->render();
}

// -------------------------------------------------------------------------------------------------
// MENU BLOCK
void Main::drawFrameMenu(){
    menuHeader->render();
    single->render();
    multi->render();
    sound->render();
    exit->render();
}

void Main::logicMenu(){
    exit->setVisible(true);
    soundObj->setSound(!sound->getState());

    if(single->getState()){
        gameState = State::SINGLE;
        exit->setVisible(false);
    } else if(multi->getState()){
        gameState = State::MULTI;
        exit->setVisible(false);
    } else if(soundObj->getSound()){
        soundObj->play(OSLSound::BACKGROUND);
    } else if(!soundObj->getSound()){
        soundObj->stopAll();
    }
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

    if(left->getState() && !player->collision(field)){
        player->setDx(NEGATIVE * player->getStep());
    } else if(right->getState() && !player->collision(field)){
        player->setDx(player->getStep());
    } else {
        player->setDx(STOP_MOVE);
        player->getCrossPoints()->clear();
    }

    enemy->collision(ball);
    ((Platform *)enemy)->collision(field);
    if(ball->collision(player) || ball->collision((Platform *)enemy))
        soundObj->play(OSLSound::BALL);

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

    if(ball->getIsOut()){
        playPause->setState(false);
        ball->setIsOut(false);
        soundObj->play(OSLSound::OUT);
    }

    if(ball->getSpeed() > 0)
        singleSpeed->setNumber(Methods::fillLeft(Methods::intToString(ball->getSpeed()), '0', 3));

    singleScoreTwo->setNumber(Methods::fillLeft(Methods::intToString((enemy->getScore())), '0', 3));
    singleScoreOne->setNumber(Methods::fillLeft(Methods::intToString((player->getScore())), '0', 3));

    ball->move();

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

    // Player one
    if(left->getState() && !player->collision(field)){
        player->setDx(NEGATIVE * player->getStep());
    } else if(right->getState() && !player->collision(field)){
        player->setDx(player->getStep());
    } else {
        player->setDx(STOP_MOVE);
        player->getCrossPoints()->clear();
    }

    // Player two
    if(leftTwo->getState() && !playerTwo->collision(field)){
        playerTwo->setDx(NEGATIVE * playerTwo->getStep());
    } else if(rightTwo->getState() && !playerTwo->collision(field)){
        playerTwo->setDx(playerTwo->getStep());
    } else {
        playerTwo->setDx(STOP_MOVE);
        playerTwo->getCrossPoints()->clear();
    }

    if(ball->collision(player) || ball->collision(playerTwo))
        soundObj->play(OSLSound::BALL);

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

    if(ball->getIsOut()){
        playPause->setState(false);
        playPauseTwo->setState(false);
        ball->setIsOut(false);
        soundObj->play(OSLSound::OUT);
    }

    // Reverse score for player one
    multiScoreOne->setNumber(Methods::fillLeft(Methods::intToString(player->getScore()), '0', 3));
    multiScoreTwo->setNumber(Methods::fillLeft(Methods::intToString(playerTwo->getScore()), '0', 3));
    ball->move();

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