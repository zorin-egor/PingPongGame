#include "Splash.h"

Splash::Splash(GLuint count,
               GLuint lifeTime,
               GLuint programID,
               GLuint textureID,
               GLuint positionAttr,
               GLuint colorStartAttr,
               GLuint colorEndAttr,
               GLuint deltaAttr,
               GLuint sizeUniform ) : m_nCount(count),
                                      m_nLifeTime(lifeTime),
                                      m_nProgramId(programID),
                                      m_nTextureId(textureID),
                                      m_nPositionAttr(positionAttr),
                                      m_nColorStartAttr(colorStartAttr),
                                      m_nColorEndAttr(colorEndAttr),
                                      m_nDeltaAttr(deltaAttr),
                                      m_nSizeUniform(sizeUniform),
                                      TOTAL_LIFE_TIME(lifeTime)
{
    LOGI("Splash::Splash()");
    m_pIsVisible = true;
    m_fPointSize = 5.0f;
    initArrays();
    setSplashPosition(0.0f, 0.0f);
}

Splash::~Splash() {
    LOGI("Splash::~Splash()");
    deleteObjects();
}

void Splash::render() {
    // Need draw this object?
    if (!m_pIsVisible) {
        return;
    }

    // Lifecycle
    if (m_nLifeTime < 0) {
        return;
    }

    setValues();

    // Use render shader program
    glUseProgram(m_nProgramId);
    checkGLError("Splash - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, m_nTextureId);
    checkGLError("Splash - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(m_nPositionAttr, 2, GL_FLOAT, GL_FALSE, 0, m_pPositionArray);
    checkGLError("Splash - glVertexAttribPointer - m_nPositionAttr");
    glEnableVertexAttribArray(m_nPositionAttr);
    checkGLError("Splash - glVertexAttribPointer - m_nPositionAttr - enabled");

    // Color start
    glVertexAttribPointer(m_nColorStartAttr, 4, GL_FLOAT, GL_FALSE, 0, m_pColorStartArray);
    checkGLError("Splash - glVertexAttribPointer - m_nColorStartAttr");
    glEnableVertexAttribArray(m_nColorStartAttr);
    checkGLError("Splash - glVertexAttribPointer - m_nColorStartAttr - enabled");

    // Color end
    glVertexAttribPointer(m_nColorEndAttr, 4, GL_FLOAT, GL_FALSE, 0, m_pColorEndArray);
    checkGLError("Splash - glVertexAttribPointer - m_nColorEndAttr");
    glEnableVertexAttribArray(m_nColorEndAttr);
    checkGLError("Splash - glVertexAttribPointer - m_nColorEndAttr - enabled");

    // Delta singleSpeed
    glVertexAttribPointer(m_nDeltaAttr, 1, GL_FLOAT, GL_FALSE, 0, m_pDeltaArray);
    checkGLError("Splash - glVertexAttribPointer - m_nDeltaAttr");
    glEnableVertexAttribArray(m_nDeltaAttr);
    checkGLError("Splash - glVertexAttribPointer - m_nDeltaAttr - enabled");

    // Size
    glUniform2f(m_nSizeUniform, m_pSizeArray[0], m_pSizeArray[1]);
    checkGLError("Splash - glUniform2f - m_nSizeUniform");

    // Draw polygon
    glDrawArrays(GL_POINTS, 0, m_nCount);
    checkGLError("Splash - glDrawArrays");
}

void Splash::initArrays() {
    // Two point * count
    m_pPositionArray = new GLfloat[m_nCount * 2];
    Methods::fillArray(m_pPositionArray, 0.0f, m_nCount * 2);

    // Delta array for mix
    m_pDeltaArray = new GLfloat[m_nCount];

    // 4 color * count
    m_pColorStartArray = new GLfloat[m_nCount * 4];
    Methods::fillArray(m_pColorStartArray, 0.0f, m_nCount * 4);

    // 4 color * count
    m_pColorEndArray = new GLfloat[m_nCount * 4];
    Methods::fillArray(m_pColorEndArray, 0.0f, m_nCount * 4);

    // Points size
    m_pSizeArray = new GLfloat[2];
    m_pSizeArray[0] = 2.0f;
    m_pSizeArray[1] = m_fPointSize;

    // dt for singleSpeed
    m_pDxArray = new GLfloat[m_nCount];
    m_pDyArray = new GLfloat[m_nCount];

    for(int i = 0; i < m_nCount; i++) {
        m_pDxArray[i] = Methods::getFullRandom() * 0.02;
        m_pDyArray[i] = Methods::getFullRandom() * 0.02;
        m_pDeltaArray[i] = Methods::getShortRandom() * 0.9;
    }
}

void Splash::setSplashPosition(GLfloat x, GLfloat y) {
    m_nLifeTime = TOTAL_LIFE_TIME;

    for(int i = 0; i < m_nCount; i++) {
        m_pPositionArray[i * 2] = x;
        m_pPositionArray[i * 2 + 1] = y;
    }
}

void Splash::setValues() {
    m_nLifeTime--;

    for(int i = 0; i < m_nCount; i++) {
        // Set new positions
        m_pPositionArray[i * 2] += m_pDxArray[i];
        m_pPositionArray[i * 2 + 1] += m_pDyArray[i];

        // Color start
        m_pColorStartArray[i * 4] = Methods::getShortRandom() * 0.5f;
        m_pColorStartArray[i * 4 + 1] = Methods::getShortRandom() * 0.5f;
        m_pColorStartArray[i * 4 + 2] = Methods::getShortRandom() * 0.5f;
        m_pColorStartArray[i * 4 + 3] = 0.1;

        // Color end
        m_pColorEndArray[i * 4] = Methods::getShortRandom() + 0.5f;
        m_pColorEndArray[i * 4 + 1] = Methods::getShortRandom() + 0.5f;
        m_pColorEndArray[i * 4 + 2] = Methods::getShortRandom() + 0.5f;
        m_pColorEndArray[i * 4 + 3] = (float) m_nLifeTime / (float) TOTAL_LIFE_TIME;
    }
}

void Splash::setParticlesCount(GLuint count) {
    m_nCount = count > 100 && count < 500 ? count : m_nCount;
}

void Splash::setParticlesSize(GLfloat size) {
    m_fPointSize = size > 2.0f && size < 20.0f ? size : m_fPointSize;
}

void Splash::deleteObjects() {
    delete [] m_pPositionArray;
    delete [] m_pColorStartArray;
    delete [] m_pColorEndArray;
    delete [] m_pDeltaArray;
    delete [] m_pSizeArray;
    delete [] m_pDxArray;
    delete [] m_pDyArray;
}

void Splash::setSettings() {
    deleteObjects();
    initArrays();
}

void Splash::resetTimer() {
    m_nLifeTime = 0;
}
