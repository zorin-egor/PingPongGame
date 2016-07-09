#include "Splash.h"

void Splash::render() {
    // Need draw this object?
    if(!isVisible)
        return;

    // Use render shader programm
    glUseProgram(programID);
    checkGLError("Particles - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGLError("Particles - glBindTexture");

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

    // Delta speed
    glVertexAttribPointer(deltaAttr, 1, GL_FLOAT, GL_FALSE, 0, deltaArray);
    checkGLError("Splash - glVertexAttribPointer - deltaAttr");
    glEnableVertexAttribArray(deltaAttr);
    checkGLError("Splash - glVertexAttribPointer - deltaAttr - enabled");

    // Size
    glUniform2f(sizeUniform, sizeArray[0], sizeArray[1]);
    checkGLError("Splash - glUniform2f - sizeUniform");


    // Draw poligon
    glDrawArrays(GL_POINTS, 0, count);
    checkGLError("Particles - glDrawArrays");
}

void Splash::initArrays(){

    // Two point * count
    positionArray = new GLfloat[count * 2];
    Methods::fillArray(positionArray, 0.0f, count * 2);

    // Delta array for mix
    deltaArray = new GLfloat[count];
    Methods::fillArray(deltaArray, 0.0f, count);

    // 4 color * count
    colorStartArray = new GLfloat[count * 4];
    Methods::fillArray(colorStartArray, 0.0f, count * 4);

    // 4 color * count
    colorEndArray = new GLfloat[count * 4];
    Methods::fillArray(colorEndArray, 0.0f, count * 4);

    // Points size
    sizeArray = new GLfloat[2];
    sizeArray[0] = 1.0f;
    sizeArray[1] = 4.0f;
}

void Splash::setValues(){



}