#include "Plume.h"

Plume::Plume(GLuint count,
             GLuint programID,
             GLuint textureID,
             GLuint positionAttr,
             GLuint colorStartAttr,
             GLuint colorEndAttr,
             GLuint deltaAttr,
             GLuint sizeUniform ) : m_nCount(count),
                                    m_nProgramID(programID),
                                    m_nTextureID(textureID),
                                    m_nPositionAttr(positionAttr),
                                    m_nColorStartAttr(colorStartAttr),
                                    m_nColorEndAttr(colorEndAttr),
                                    m_nDeltaAttr(deltaAttr),
                                    m_nSizeUniform(sizeUniform),
                                    MAX_COUNT(count),
                                    MAX_SIZE(7.0f),
                                    MIN_SIZE(2.0f)
{
    LOGI("Plume::Plume()");
    m_bIsVisible = true;
    m_fPointSize = MAX_SIZE;
    initArrays();
}

Plume::~Plume() {
    LOGI("Plume::~Plume()");
    deleteObjects();
}

void Plume::render() {
    // Need draw this object?
    if (!m_bIsVisible) {
        return;
    }

    setValues();

    // Use render shader programm
    glUseProgram(m_nProgramID);
    checkGLError("Plume - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, m_nTextureID);
    checkGLError("Plume - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(m_nPositionAttr, 2, GL_FLOAT, GL_FALSE, 0, m_pPositionArray);
    checkGLError("Plume - glVertexAttribPointer - m_nPositionAttr");
    glEnableVertexAttribArray(m_nPositionAttr);
    checkGLError("Plume - glVertexAttribPointer - m_nPositionAttr - enabled");

    // Color start
    glVertexAttribPointer(m_nColorStartAttr, 4, GL_FLOAT, GL_FALSE, 0, m_pColorStartArray);
    checkGLError("Plume - glVertexAttribPointer - m_nColorStartAttr");
    glEnableVertexAttribArray(m_nColorStartAttr);
    checkGLError("Plume - glVertexAttribPointer - m_nColorStartAttr - enabled");

    // Color end
    glVertexAttribPointer(m_nColorEndAttr, 4, GL_FLOAT, GL_FALSE, 0, m_pColorEndArray);
    checkGLError("Plume - glVertexAttribPointer - m_nColorEndAttr");
    glEnableVertexAttribArray(m_nColorEndAttr);
    checkGLError("Plume - glVertexAttribPointer - m_nColorEndAttr - enabled");

    // Delta m_pSingleSpeed
    glVertexAttribPointer(m_nDeltaAttr, 1, GL_FLOAT, GL_FALSE, 0, m_pDeltaArray);
    checkGLError("Plume - glVertexAttribPointer - m_nDeltaAttr");
    glEnableVertexAttribArray(m_nDeltaAttr);
    checkGLError("Plume - glVertexAttribPointer - m_nDeltaAttr - enabled");

    // Size
    glUniform2f(m_nSizeUniform, m_pSizeArray[0], m_pSizeArray[1]);
    checkGLError("Plume - glUniform2f - m_nSizeUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, m_nCount);
    checkGLError("Plume - glDrawArrays");
}

void Plume::initArrays() {
    // Two point * count
    m_pPositionArray = new GLfloat[MAX_COUNT * 2];
    Methods::fillArray(m_pPositionArray, 0.0f, MAX_COUNT * 2);

    // Delta array for mix
    m_pDeltaArray = new GLfloat[MAX_COUNT];
    for(int i = 0; i < MAX_COUNT; i++) {
        m_pDeltaArray[i] = Methods::getShortRandom() * 0.9;
    }

    // 4 color * count
    m_pColorStartArray = new GLfloat[MAX_COUNT * 4];
    Methods::fillArray(m_pColorStartArray, 0.0f, MAX_COUNT * 4);

    // 4 color * count
    m_pColorEndArray = new GLfloat[MAX_COUNT * 4];
    Methods::fillArray(m_pColorEndArray, 0.0f, MAX_COUNT * 4);

    // Points size
    m_pSizeArray = new GLfloat[2];
    m_pSizeArray[0] = MIN_SIZE;
    m_pSizeArray[1] = m_fPointSize;
}

void Plume::setValues() {
    for(int i = 0; i < MAX_COUNT; i++) {
        // Color start
        m_pColorStartArray[i * 4] = Methods::getShortRandom() * 0.5f;
        m_pColorStartArray[i * 4 + 1] = Methods::getShortRandom() * 0.5f;
        m_pColorStartArray[i * 4 + 2] = Methods::getShortRandom() * 0.5f;
        m_pColorStartArray[i * 4 + 3] = 0.1f;

        // Color end
        m_pColorEndArray[i * 4] = Methods::getShortRandom() + 0.5f;
        m_pColorEndArray[i * 4 + 1] = Methods::getShortRandom() + 0.5f;
        m_pColorEndArray[i * 4 + 2] = Methods::getShortRandom() + 0.5f;
    }
}

void Plume::setPlumePoints(std::queue<GLfloat> * points) {
    if (points->size() > 0 && points->size() < MAX_COUNT && points->size() % 2 == 0) {
        std::queue<GLfloat> plumePoints(*points);
        unsigned int halfQueue = points->size() / 2;
        unsigned int pointsPerStep = MAX_COUNT / halfQueue;
        m_nCount = pointsPerStep * halfQueue;
        unsigned int i = 0;
        float dispersion = 0.008f;
        float alpha = 0.005f;

        while(plumePoints.size() > 0) {
            GLfloat x = plumePoints.front();
            plumePoints.pop();
            GLfloat y = plumePoints.front();
            plumePoints.pop();

            for(int j = 0; j < pointsPerStep; j++, i++) {
                // Set plume position
                m_pPositionArray[i * 2] = x + Methods::getFullRandom() * dispersion;
                m_pPositionArray[i * 2 + 1] = y + Methods::getFullRandom() * dispersion;

                // Set alpha of tale
                m_pColorEndArray[i * 4 + 3] = alpha;
            }

            dispersion += 0.002f;
            alpha += 0.05f;
        }
    }
}

void Plume::setParticlesCount(GLuint count) {
    m_nCount = count > 100 && count < 500 ? m_nCount : count;
}

void Plume::setParticlesSize(GLfloat size) {
    m_fPointSize = size > 2.0f && size < 20.0f ? size : m_fPointSize;
}

void Plume::deleteObjects() {
    delete [] m_pPositionArray;
    delete [] m_pColorStartArray;
    delete [] m_pColorEndArray;
    delete [] m_pDeltaArray;
    delete [] m_pSizeArray;
}

void Plume::setSettings() {
    deleteObjects();
    initArrays();
}