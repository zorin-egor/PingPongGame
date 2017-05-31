#include "Shape.h"

const GLfloat Shape::STATIC_FIGURES[20][4] =    {
                                                    { 3.941473f, 2.242605f, 3.341472f, 2.392605f },
                                                    { 4.266757f, 2.573080f, 4.816757f, 2.473080f },
                                                    { 3.533157f, 2.268258f, 3.183159f, 1.768258f },
                                                    { 1.658111f, 1.950000f, 2.408111f, 1.550000f }
                                                };

void Shape::render() {
    //LOGI("Graphic::render(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, count, radius[0], radius[1]);
    // Need draw this object?
    if(!isVisible)
        return;

    setValues();

    // Use render shader program
    glUseProgram(programID);
    checkGLError("Graphic - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGLError("Graphic - glBindTexture");

    // Fill attributes and uniforms
    // Init position
    glVertexAttribPointer(starsAngle, 1, GL_FLOAT, GL_FALSE, 0, arrayPosition);
    checkGLError("Graphic - glVertexAttribPointer - graphicAngle");
    glEnableVertexAttribArray(starsAngle);
    checkGLError("Graphic - glVertexAttribPointer - graphicAngle - enabled");

    // For color
    glVertexAttribPointer(starColor, 4, GL_FLOAT, GL_FALSE, 0, arrayColor);
    checkGLError("Graphic - glVertexAttribPointer - graphicColor");
    glEnableVertexAttribArray(starColor);
    checkGLError("Graphic - glVertexAttribPointer - graphicColor - enabled");

    // Center
    glUniform2f(starCenter, centerX, centerY);
    checkGLError("Graphic - glUniform2f - graphicCenter");

    // Radius
    glUniform2f(starRadius, radiusX, radiusY);
    checkGLError("Graphic - glUniform2f - graphicRadius");

    // Arguments
    glUniform4f(starArguments, arguments[0], arguments[1], arguments[2], arguments[3]);
    checkGLError("Graphic - glUniform4f - graphicArguments");

    // Size of point
    glUniform1f(starSize, pointSize);
    checkGLError("Graphic - glUniform1f - graphicSize");

    // Delta speed
    glUniform1f(starTotalDeltaSpeed, totalDeltaSpeed);
    checkGLError("Graphic - glUniform2f - deltaPositionUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, count);
    checkGLError("Graphic - glDrawArrays");

    // Off attributes
    glDisableVertexAttribArray(starsAngle);
    glDisableVertexAttribArray(starColor);
}

void Shape::init(){
    // Parameters for functions
    // Default arguments
    Methods::fillArray(arguments, 1.0f, SIZE_ARRAYS);
    // For static type
    GLuint randRow = Methods::getStrictRandom(4);
    arguments[0] = STATIC_FIGURES[randRow][0];
    arguments[1] = STATIC_FIGURES[randRow][1];
    arguments[2] = STATIC_FIGURES[randRow][2];
    arguments[3] = STATIC_FIGURES[randRow][3];

    // Delta speed
    dParticlesSpeed = 0.005f;
    // Current speed
    totalDeltaSpeed = 0.0f;

    // Init colors
    arrayColor = new GLfloat[count * 4];
    Methods::fillArrayRGBA(arrayColor, count, 0.8f, 0.0f, 0.0f, 1.0f);

    for(int i = 0; i < count / 2; i++){
        arrayColor[i * 4] = 0.0f;
        arrayColor[i * 4 + 1] = 0.0f;
        arrayColor[i * 4 + 2] = 0.8f;
        arrayColor[i * 4 + 3] = 0.7f;
    }

    // Initial position
    arrayPosition = new GLfloat[count];
    for(int i = 0; i < count; i++)
        arrayPosition[i] = (GLfloat)i;

    //LOGI("Graphic::init - ARGS(); %ff, %ff, %ff, %ff", arguments[0], arguments[1], arguments[2], arguments[3]);
}

void Shape::setValues(){
    // For change common points direction
    if(totalDeltaSpeed > STRICT_SPEED_MAX || totalDeltaSpeed < STRICT_SPEED_MIN)
        dParticlesSpeed = -dParticlesSpeed;
    totalDeltaSpeed += dParticlesSpeed;

    LOGI("Graphic::setValues - ARGS(); %ff, %ff, %ff, %ff", arguments[0], arguments[1], arguments[2], arguments[3]);
    //LOGI("Graphic::setValues - DELTA(); %ff, %ff, %ff, %ff", dArgumentsTransformSpeed[0], dArgumentsTransformSpeed[1], dArgumentsTransformSpeed[2], dArgumentsTransformSpeed[3]);
}

void Shape::setSettings(){
    delete [] arrayPosition;
    delete [] arrayColor;
    init();
}