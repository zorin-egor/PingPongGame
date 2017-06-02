#include "Shape.h"

const GLfloat Shape::STATIC_FIGURES[30][4] =    {
                                                    { 3.941473f, 2.242605f, 3.341472f, 2.392605f },
                                                    { 4.266757f, 2.573080f, 4.816757f, 2.473080f },
                                                    { 2.991552f, 5.303362f, 2.641552f, 5.703362f },
                                                    { 5.166590f, 3.200857f, 4.816589f, 3.286608f },
                                                    { 2.466584f, 1.821339f, 2.316585f, 1.871339f },
                                                    { 2.541554f, 3.581697f, 2.341554f, 3.931697f },
                                                    { 2.133250f, 4.303725f, 1.533250f, 4.453724f },
                                                    { 2.258382f, 3.602231f, 1.658382f, 3.752230f },
                                                    { 1.916898f, 2.546700f, 1.316898f, 2.696700f },
                                                    { 3.391655f, 4.172695f, 3.141655f, 4.522695f },
                                                    { 2.783147f, 4.595323f, 2.833147f, 4.345323f },
                                                    { 1.627712f, 3.734871f, 2.027712f, 4.534871f },
                                                    { 1.833125f, 2.745408f, 2.383124f, 3.195408f },
                                                    { 5.799956f, 3.344940f, 5.849955f, 3.394940f }
                                                };

void Shape::render() {
    //LOGI("Shape::render(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, count, radius[0], radius[1]);
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
    GLuint randRow = Methods::getStrictRandom(14);
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
    colorParts = COLOR_EQUALS_PARTS;
    setColor();
    //setColorLight();

    // Initial position
    arrayPosition = new GLfloat[count];
    for(int i = 0; i < count; i++)
        arrayPosition[i] = (GLfloat)i;

    //LOGI("Shape::init - ARGS(); %ff, %ff, %ff, %ff", arguments[0], arguments[1], arguments[2], arguments[3]);
}

void Shape::setValues(){
    // For change common points direction
    if(totalDeltaSpeed > STRICT_SPEED_MAX || totalDeltaSpeed < STRICT_SPEED_MIN)
        dParticlesSpeed = -dParticlesSpeed;
    totalDeltaSpeed += dParticlesSpeed;

    if(isColorReset && colorResetTimer-- < 0){
        setColor();
        isColorReset = false;
    }

    //LOGI("Shape::setValues - colorResetTimer: %d", colorResetTimer);
    //LOGI("Shape::setValues - ARGS(); %ff, %ff, %ff, %ff", arguments[0], arguments[1], arguments[2], arguments[3]);
    //LOGI("Shape::setValues - DELTA(); %ff, %ff, %ff, %ff", dArgumentsTransformSpeed[0], dArgumentsTransformSpeed[1], dArgumentsTransformSpeed[2], dArgumentsTransformSpeed[3]);
}

void Shape::setSettings(){
    delete [] arrayPosition;
    delete [] arrayColor;
    init();
}

void Shape::setColor(){
    Methods::fillArrayRGBA(arrayColor, 0, count * colorParts, 0.0f, 0.0f, 1.0f, 0.6f);
    Methods::fillArrayRGBA(arrayColor, count * colorParts, count, 0.8f, 0.0f, 0.0f, 0.6f);
}

void Shape::setColorLight(){
    Methods::fillArrayRGBA(arrayColor, 0, count, 1.0f, 0.922f, 0.804f, 0.8f);
}

void Shape::setColorPart(GLuint first, GLuint second){
    colorParts = COLOR_EQUALS_PARTS;
    if(first != second)
        colorParts = (GLfloat)first / (GLfloat)(first + second);
    //LOGI("Shape::setColorPart - colorParts: %ff", colorParts);
}

void Shape::setColorTimer(){
    colorResetTimer = COLOR_INITIAL_TIMER;
    isColorReset = true;
}