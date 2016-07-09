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
    particles = new Particles(1000,
                              sprites,
                              textures->getTexturesPackIDs(ManageTexture::STAR),
                              spritesRandomPosition,
                              spritesRandomSpeed,
                              spritesRandomRadius,
                              spritesDelta,
                              spritesColorStart,
                              spritesColorEnd,
                              spritesSize,
                              spritesTotalDeltaSpeed);

    splashObj = new Splash( 100, 50,
                            splash,
                            textures->getTexturesPackIDs(ManageTexture::SPLASH),
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
    bordDown = new View(textures->getTexturesPackIDs(ManageTexture::BORD_DOWN),
                        polygons,
                        polygonsPositionAttr,
                        polygonsTextureAttr,
                        polygonsTransformationAttr,
                        setBordDownPosition(matrix->getDefaultVerticesCoords()),
                        matrix->getDefaultTextureCoord(),
                        matrix->getDefaultMatrix4x4());



    // Bord up
    bordUp = new View(textures->getTexturesPackIDs(ManageTexture::BORD_UP),
                        polygons,
                        polygonsPositionAttr,
                        polygonsTextureAttr,
                        polygonsTransformationAttr,
                        setBordUpPosition(matrix->getDefaultVerticesCoords()),
                        matrix->getDefaultTextureCoord(),
                        matrix->getDefaultMatrix4x4());

    // Left button
    left = new Button(false,
                      true,
                      -0.95f, -0.75f, BUTTON_CONTROL_WIDTH, BUTTON_CONTROL_HEIGHT,
                      textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                      polygons,
                      polygonsPositionAttr,
                      polygonsTextureAttr,
                      polygonsTransformationAttr,
                      matrix->getDefaultVerticesCoords(),
                      Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::ONE),
                      matrix->getDefaultMatrix4x4());

    // Right button
    right = new Button(false,
                       true,
                       0.3f, -0.75f, BUTTON_CONTROL_WIDTH, BUTTON_CONTROL_HEIGHT,
                       textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                       polygons,
                       polygonsPositionAttr,
                       polygonsTextureAttr,
                       polygonsTransformationAttr,
                       matrix->getDefaultVerticesCoords(),
                       Matrix::setTextureCoords(matrix->getDefaultTextureCoord(),  2, 2, Matrix::ONE),
                       matrix->getDefaultMatrix4x4());

    // Play pause button
    playPause = new Button(true,
                           false,
                           -0.22f, -0.75f, BUTTON_START_WIDTH, BUTTON_START_HEIGHT,
                           textures->getTexturesPackIDs(ManageTexture::BUTTONS),
                           polygons,
                           polygonsPositionAttr,
                           polygonsTextureAttr,
                           polygonsTransformationAttr,
                           matrix->getDefaultVerticesCoords(),
                           Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::THREE),
                           matrix->getDefaultMatrix4x4());

    // Label of speed
    speed = new Label(  matrix,
                        -0.5f, 0.95f, LABEL_WIDTH, LABEL_HEIGHT,
                        textures->getTexturesPackIDs(ManageTexture::NUMBERS),
                        polygons,
                        polygonsPositionAttr,
                        polygonsTextureAttr,
                        polygonsTransformationAttr,
                        "000");

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
    enemy = new Enemy( PLATFORMS_SPEED + 0.04,
                        -0.25, 0.75f, PLATFORMS_WIDTH, PLATFORMS_HEIGHT,
                        textures->getTexturesPackIDs(ManageTexture::OBJECTS),
                        polygons,
                        polygonsPositionAttr,
                        polygonsTextureAttr,
                        polygonsTransformationAttr,
                        matrix->getDefaultVerticesCoords(),
                        Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::TWO),
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
                    Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 2, 2, Matrix::THREE),
                    matrix->getDefaultMatrix4x4());
}

void Main::step(){
    // Clear screen
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    checkGLError("Main::step - glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGLError("Main::step - glClear");

    // Logic
    if(playPause->getState())
        logic();

    // Draw
    drawFrame();
}

void Main::drawFrame(){
    // Draw something under
    //renderBackground();
    //renderObjects();
    //renderInterface();

    splashObj->render();
}

void Main::logic(){

    if(left->getState() && !player->collision(field)){
        player->setDx(NEGATIVE * player->getStep());
    } else if(right->getState() && !player->collision(field)){
                player->setDx(player->getStep());
            } else {
                    player->setDx(STOP_MOVE);
                    player->getCrossPoints()->clear();
                }

    enemy->collision(ball);
    ball->collision(player);
    ball->collision((Platform *)enemy);
    ball->collision(field);

    if(ball->getIsOut()){
        playPause->setState(false);
        ball->setIsOut(false);
    }

    speed->setNumber(Methods::fillLeft(Methods::intToString((int)(ball->getStep() * 1000.0f)), '0', 4));
    ball->move();
}

void Main::rotateBackground(){
    if(deltaRotate >= CENTER_ROTATE)
        deltaRotate = NEGATIVE * CENTER_ROTATE;

    center->setTransformationMatrix(Matrix::setRotateMatrix4x4(Matrix::setRotateMatrix4x4(center->getTransformationMatrix(), deltaRotate += CENTER_SPEED, Matrix::X), deltaRotate, Matrix::Z));
    center->render();
}

GLfloat * Main::setBordDownPosition(GLfloat * positionCoords){
    positionCoords[1] = BORDER_DOWN;
    positionCoords[7] = BORDER_DOWN;
    return positionCoords;
}

GLfloat * Main::setBordUpPosition(GLfloat * positionCoords){
    positionCoords[3] = BORDER_UP;
    positionCoords[5] = BORDER_UP;
    return positionCoords;
}

void Main::renderBackground(){
    // Background
    background->render();

    // Rotate background
    rotateBackground();

    // Particles
    particles->render();
}

void Main::renderInterface(){
    // Bord down
    bordDown->render();

    // Bord up
    bordUp->render();

    // Speed
    speed->render();

    // Button left
    left->render();

    // Button right
    right->render();

    // Button playPause
    playPause->render();
}

void Main::renderObjects(){
    // Ball
    ball->render();

    // Player
    player->render();

    // Enemy
    enemy->render();
}