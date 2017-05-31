#include <string.h>
#include <Common/Methods.h>
#include "Particles.h"

void Particles::render() {
    // Need draw this object?
    if(!isVisible)
        return;

    setValues();

    // Use render shader programm
    glUseProgram(programID);
    checkGLError("Particles - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGLError("Particles - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(randomPositionAttr, 2, GL_FLOAT, GL_FALSE, 0, randomArrayCoords);
    checkGLError("Particles - glVertexAttribPointer - randomPositionAttr");
    glEnableVertexAttribArray(randomPositionAttr);
    checkGLError("Particles - glVertexAttribPointer - randomPositionAttr - enabled");

    // Speed
    glVertexAttribPointer(randomSpeedAttr, 1, GL_FLOAT, GL_FALSE, 0, randomArraySpeed);
    checkGLError("Particles - glVertexAttribPointer - randomSpeedAttr");
    glEnableVertexAttribArray(randomSpeedAttr);
    checkGLError("Particles - glVertexAttribPointer - randomSpeedAttr - enabled");

    // Radius
    glVertexAttribPointer(randomRadiusAttr, 1, GL_FLOAT, GL_FALSE, 0, randomArrayRadius);
    checkGLError("Particles - glVertexAttribPointer - randomRadiusAttr");
    glEnableVertexAttribArray(randomRadiusAttr);
    checkGLError("Particles - glVertexAttribPointer - randomRadiusAttr - enabled");

    // Delta
    glVertexAttribPointer(deltaAttr, 1, GL_FLOAT, GL_FALSE, 0, randomArrayDelta);
    checkGLError("Particles - glVertexAttribPointer - deltaAttr");
    glEnableVertexAttribArray(deltaAttr);
    checkGLError("Particles - glVertexAttribPointer - deltaAttr - enabled");

    // Color start
    glVertexAttribPointer(colorStartAttr, 4, GL_FLOAT, GL_FALSE, 0, colorStartArray);
    checkGLError("Particles - glVertexAttribPointer - colorStartAttr");
    glEnableVertexAttribArray(colorStartAttr);
    checkGLError("Particles - glVertexAttribPointer - colorStartAttr - enabled");

    // Color end
    glVertexAttribPointer(colorEndAttr, 4, GL_FLOAT, GL_FALSE, 0, colorEndArray);
    checkGLError("Particles - glVertexAttribPointer - colorEndAttr");
    glEnableVertexAttribArray(colorEndAttr);
    checkGLError("Particles - glVertexAttribPointer - colorEndAttr - enabled");

    // Size
    glUniform2f(sizeUniform, sizeUniformArray[0], sizeUniformArray[1]);
    checkGLError("Particles - glUniform2f - sizeUniform");

    // Total singleSpeed
    glUniform1f(totalDeltaSpeedUniform, totalDeltaSpeed);
    checkGLError("Particles - glUniform2f - totalDeltaSpeedUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, count);
    checkGLError("Particles - glDrawArrays");
}

void Particles::initArrays(){
    // Two point * count
    positionArray = new GLfloat[count * 2];
    Methods::fillArray(positionArray, 0.0f, count * 2);

    // 4 color * count
    colorStartArray = new GLfloat[count * 4];
    Methods::fillArray(colorStartArray, 0.0f, count * 4);

    // 4 color * count
    colorEndArray = new GLfloat[count * 4];
    Methods::fillArray(colorEndArray, 0.0f, count * 4);

    // delta * count
    sizeUniformArray = new GLfloat[2];
    sizeUniformArray[0] = 2.0f;
    sizeUniformArray[1] = pointSize;

    // Random coords
    randomArrayCoords = new GLfloat[count * 2];
    for(int i = 0; i < count * 2; i++)
        randomArrayCoords[i] = Methods::getFullRandom() * 0.9f;

    // Random radius
    randomArrayRadius = new GLfloat[count];
    for(int i = 0; i < count; i++)
        randomArrayRadius[i] = Methods::getShortRandom();

    // Random singleSpeed
    randomArraySpeed = new GLfloat[count];
    for(int i = 0; i < count; i++)
        randomArraySpeed[i] = Methods::getShortRandom() * 0.5f;

    // Random delta
    randomArrayDelta = new GLfloat[count];
    for(int i = 0; i < count; i++)
        randomArrayDelta[i] = Methods::getShortRandom();

}

void Particles::setValues(){

    if(totalDeltaSpeed > 1000.0f || totalDeltaSpeed < 0.0f)
        deltaSpeed *= -1.0f;

    totalDeltaSpeed = totalDeltaSpeed + deltaSpeed;

    for(int i = 0; i < count; i++){
        // Color start
        colorStartArray[i * 4] = Methods::getShortRandom() * 0.5f;
        colorStartArray[i * 4 + 1] = Methods::getShortRandom() * 0.5f;
        colorStartArray[i * 4 + 2] = Methods::getShortRandom() * 0.5f;
        colorStartArray[i * 4 + 3] = 0.3f;

        // Color end
        colorEndArray[i * 4] = Methods::getShortRandom() + 0.5f;
        colorEndArray[i * 4 + 1] = Methods::getShortRandom() + 0.5f;
        colorEndArray[i * 4 + 2] = Methods::getShortRandom() + 0.5f;
        colorEndArray[i * 4 + 3] = 0.95f;
    }
}

