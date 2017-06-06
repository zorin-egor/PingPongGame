#include "Splash.h"

void Splash::render() {
    // Need draw this object?
    if(!isVisible)
        return;

    // Lifecycle
    if(lifeTime < 0)
        return;

    setValues();

    // Use render shader programm
    glUseProgram(programID);
    checkGLError("Splash - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGLError("Splash - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(positionAttr, 2, GL_FLOAT, GL_FALSE, 0, positionArray);
    checkGLError("Splash - glVertexAttribPointer - positionAttr");
    glEnableVertexAttribArray(positionAttr);
    checkGLError("Splash - glVertexAttribPointer - positionAttr - enabled");

    // Color start
    glVertexAttribPointer(colorStartAttr, 4, GL_FLOAT, GL_FALSE, 0, colorStartArray);
    checkGLError("Splash - glVertexAttribPointer - colorStartAttr");
    glEnableVertexAttribArray(colorStartAttr);
    checkGLError("Splash - glVertexAttribPointer - colorStartAttr - enabled");

    // Color end
    glVertexAttribPointer(colorEndAttr, 4, GL_FLOAT, GL_FALSE, 0, colorEndArray);
    checkGLError("Splash - glVertexAttribPointer - colorEndAttr");
    glEnableVertexAttribArray(colorEndAttr);
    checkGLError("Splash - glVertexAttribPointer - colorEndAttr - enabled");

    // Delta singleSpeed
    glVertexAttribPointer(deltaAttr, 1, GL_FLOAT, GL_FALSE, 0, deltaArray);
    checkGLError("Splash - glVertexAttribPointer - deltaAttr");
    glEnableVertexAttribArray(deltaAttr);
    checkGLError("Splash - glVertexAttribPointer - deltaAttr - enabled");

    // Size
    glUniform2f(sizeUniform, sizeArray[0], sizeArray[1]);
    checkGLError("Splash - glUniform2f - sizeUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, count);
    checkGLError("Splash - glDrawArrays");
}

void Splash::initArrays(){
    // Two point * count
    positionArray = new GLfloat[count * 2];
    Methods::fillArray(positionArray, 0.0f, count * 2);

    // Delta array for mix
    deltaArray = new GLfloat[count];

    // 4 color * count
    colorStartArray = new GLfloat[count * 4];
    Methods::fillArray(colorStartArray, 0.0f, count * 4);

    // 4 color * count
    colorEndArray = new GLfloat[count * 4];
    Methods::fillArray(colorEndArray, 0.0f, count * 4);

    // Points size
    sizeArray = new GLfloat[2];
    sizeArray[0] = 2.0f;
    sizeArray[1] = pointSize;

    // dt for singleSpeed
    dxArray = new GLfloat[count];
    dyArray = new GLfloat[count];
    for(int i = 0; i < count; i++){
        dxArray[i] = Methods::getFullRandom() * 0.02;
        dyArray[i] = Methods::getFullRandom() * 0.02;
        deltaArray[i] = Methods::getShortRandom() * 0.9;
    }
}

void Splash::setSplashPosition(GLfloat _x, GLfloat _y){
    lifeTime = TOTAL_LIFE_TIME;

    for(int i = 0; i < count; i++){
        positionArray[i * 2] = _x;
        positionArray[i * 2 + 1] = _y;
    }
}

void Splash::setValues(){
    lifeTime--;

    for(int i = 0; i < count; i++){

        // Set new positions
        positionArray[i * 2] += dxArray[i];
        positionArray[i * 2 + 1] += dyArray[i];

        // Color start
        colorStartArray[i * 4] = Methods::getShortRandom() * 0.5f;
        colorStartArray[i * 4 + 1] = Methods::getShortRandom() * 0.5f;
        colorStartArray[i * 4 + 2] = Methods::getShortRandom() * 0.5f;
        colorStartArray[i * 4 + 3] = 0.1;

        // Color end
        colorEndArray[i * 4] = Methods::getShortRandom() + 0.5f;
        colorEndArray[i * 4 + 1] = Methods::getShortRandom() + 0.5f;
        colorEndArray[i * 4 + 2] = Methods::getShortRandom() + 0.5f;
        colorEndArray[i * 4 + 3] = (float) lifeTime / (float) TOTAL_LIFE_TIME;
    }
}

void Splash::setParticlesCount(GLuint _count){
    count = _count > 100 && _count < 500? _count : count;
}

void Splash::setParticlesSize(GLfloat _size){
    pointSize = _size > 2.0f && _size < 20.0f ? _size : pointSize;
}

void Splash::deleteObjects(){
    delete [] positionArray;
    delete [] colorStartArray;
    delete [] colorEndArray;
    delete [] deltaArray;
    delete [] sizeArray;
    delete [] dxArray;
    delete [] dyArray;
}

void Splash::setSettings(){
    deleteObjects();
    initArrays();
}

void Splash::resetTimer(){
    lifeTime = 0;
}
