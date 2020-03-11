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

Shape::Shape(GLuint count,
             GLfloat centerX,
             GLfloat centerY,
             GLfloat radiusX,
             GLfloat radiusY,
             GLuint programID,
             GLuint textureID,
             GLuint starsAngle,
             GLuint starColor,
             GLuint starCenter,
             GLuint starRadius,
             GLuint starArguments,
             GLuint starSize,
             GLuint starTotalDeltaSpeed) : m_nCount(count),
                                           CENTER_X(centerX),
                                           CENTER_Y(centerY),
                                           RADIUS_X(radiusX),
                                           RADIUS_Y(radiusY),
                                           m_nProgramID(programID),
                                           m_nTextureID(textureID),
                                           m_nStarsAngle(starsAngle),
                                           m_nStarColor(starColor),
                                           m_nStarCenter(starCenter),
                                           m_nStarRadius(starRadius),
                                           m_nStarArguments(starArguments),
                                           m_nStarSize(starSize),
                                           m_nStarTotalDeltaSpeed(starTotalDeltaSpeed),
                                           STRICT_SPEED_MAX(10000.0f),
                                           STRICT_SPEED_MIN(0.0f),
                                           m_fPointSize(10.0f),
                                           COLOR_EQUALS_PARTS(0.5f),
                                           COLOR_INITIAL_TIMER(10)
{
    LOGI("Shape::Shape()");
    m_bIsVisible = true;
    m_bIsColorReset = false;
    m_fColorParts = COLOR_EQUALS_PARTS;
    m_nColorResetTimer = COLOR_INITIAL_TIMER;
    initArrays();
}

Shape::~Shape() {
    LOGI("Shape::~Shape()");
    // Off attributes
    //glDisableVertexAttribArray(m_nStarsAngle);
    //glDisableVertexAttribArray(m_nStarColor);
    deleteObjects();
}

void Shape::render() {
    //LOGI("Shape::render(); Cx: %f; Cy: %f; Cc: %d; Rx: %f; Ry: %f;", CENTER_X, CENTER_Y, count, radius[0], radius[1]);
    // Need draw this object?
    if (!m_bIsVisible) {
        return;
    }

    setValues();

    // Use render shader program
    glUseProgram(m_nProgramID);
    checkGLError("Graphic - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, m_nTextureID);
    checkGLError("Graphic - glBindTexture");

    // Fill attributes and uniforms
    // Init position
    glVertexAttribPointer(m_nStarsAngle, 1, GL_FLOAT, GL_FALSE, 0, m_fArrayPosition);
    checkGLError("Graphic - glVertexAttribPointer - m_nStarsAngle");
    glEnableVertexAttribArray(m_nStarsAngle);
    checkGLError("Graphic - glVertexAttribPointer - m_nStarsAngle - enabled");

    // For color
    glVertexAttribPointer(m_nStarColor, 4, GL_FLOAT, GL_FALSE, 0, m_fArrayColor);
    checkGLError("Graphic - glVertexAttribPointer - m_nStarColor");
    glEnableVertexAttribArray(m_nStarColor);
    checkGLError("Graphic - glVertexAttribPointer - m_nStarColor - enabled");

    // Center
    glUniform2f(m_nStarCenter, CENTER_X, CENTER_Y);
    checkGLError("Graphic - glUniform2f - m_nStarCenter");

    // Radius
    glUniform2f(m_nStarRadius, RADIUS_X, RADIUS_Y);
    checkGLError("Graphic - glUniform2f - m_nStarRadius");

    // Arguments
    glUniform4f(m_nStarArguments, m_fArguments[0], m_fArguments[1], m_fArguments[2], m_fArguments[3]);
    checkGLError("Graphic - glUniform4f - m_nStarArguments");

    // Size of point
    glUniform1f(m_nStarSize, m_fPointSize);
    checkGLError("Graphic - glUniform1f - m_nStarSize");

    // Delta speed
    glUniform1f(m_nStarTotalDeltaSpeed, m_fTotalDeltaSpeed);
    checkGLError("Graphic - glUniform2f - m_nStarTotalDeltaSpeed");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, m_nCount);
    checkGLError("Graphic - glDrawArrays");

    // Off attributes
    glDisableVertexAttribArray(m_nStarsAngle);
    glDisableVertexAttribArray(m_nStarColor);
}

void Shape::initArrays() {
    // Parameters for functions
    // Default arguments
    Methods::fillArray(m_fArguments, 1.0f, SIZE_ARRAYS);

    // For static type
    GLuint randRow = Methods::getStrictRandom(14);
    m_fArguments[0] = STATIC_FIGURES[randRow][0];
    m_fArguments[1] = STATIC_FIGURES[randRow][1];
    m_fArguments[2] = STATIC_FIGURES[randRow][2];
    m_fArguments[3] = STATIC_FIGURES[randRow][3];

    // Delta speed
    m_fParticlesSpeed = 0.005f;
    // Current speed
    m_fTotalDeltaSpeed = 0.0f;

    // Init colors
    m_fArrayColor = new GLfloat[m_nCount * 4];
    m_fColorParts = COLOR_EQUALS_PARTS;
    setColor();
    //setColorLight();

    // Initial position
    m_fArrayPosition = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++) {
        m_fArrayPosition[i] = (GLfloat)i;
    }

    //LOGI("Shape::initArrays - ARGS(); %ff, %ff, %ff, %ff", arguments[0], arguments[1], arguments[2], arguments[3]);
}

void Shape::setValues() {
    // For change common points direction
    if (m_fTotalDeltaSpeed > STRICT_SPEED_MAX || m_fTotalDeltaSpeed < STRICT_SPEED_MIN) {
        m_fParticlesSpeed = -m_fParticlesSpeed;
    }

    m_fTotalDeltaSpeed += m_fParticlesSpeed;

    if (m_bIsColorReset && m_nColorResetTimer-- < 0) {
        setColor();
        m_bIsColorReset = false;
    }

    //LOGI("Shape::setValues - m_nColorResetTimer: %d", m_nColorResetTimer);
    //LOGI("Shape::setValues - ARGS(); %ff, %ff, %ff, %ff", arguments[0], arguments[1], arguments[2], arguments[3]);
    //LOGI("Shape::setValues - DELTA(); %ff, %ff, %ff, %ff", dArgumentsTransformSpeed[0], dArgumentsTransformSpeed[1], dArgumentsTransformSpeed[2], dArgumentsTransformSpeed[3]);
}

void Shape::setSettings() {
    deleteObjects();
    initArrays();
}

void Shape::setColor() {
    Methods::fillArrayRGBA(m_fArrayColor, 0, m_nCount * m_fColorParts, 0.0f, 0.0f, 1.0f, 1.0f);
    Methods::fillArrayRGBA(m_fArrayColor, m_nCount * m_fColorParts, m_nCount, 1.0f, 0.0f, 0.0f, 1.0f);
}

void Shape::setColorLight() {
    Methods::fillArrayRGBA(m_fArrayColor, 0, m_nCount, 1.0f, 0.922f, 0.804f, 0.8f);
}

void Shape::setColorPart(GLuint first, GLuint second) {
    m_fColorParts = COLOR_EQUALS_PARTS;
    if (first != second) {
        m_fColorParts = (GLfloat)first / (GLfloat)(first + second);
    }
    //LOGI("Shape::setColorPart - m_fColorParts: %ff", m_fColorParts);
}

void Shape::setColorTimer() {
    m_nColorResetTimer = COLOR_INITIAL_TIMER;
    m_bIsColorReset = true;
}

void Shape::setParticlesCount(GLuint count) {
    m_nCount = count > 5000 && count < 30000 ? count : m_nCount;
}

void Shape::setParticlesSize(GLfloat size) {
    m_fPointSize = size > 0.0f && size < 100.0f ? size : m_fPointSize;
}

void Shape::deleteObjects() {
    delete [] m_fArrayPosition;
    delete [] m_fArrayColor;
}