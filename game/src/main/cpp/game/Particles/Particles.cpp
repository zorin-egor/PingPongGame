#include <string.h>
#include <Common/Methods.h>
#include "Particles.h"

Particles::Particles(GLuint count,
                     GLuint programId,
                     GLuint textureId,
                     GLuint randomPositionAttr,
                     GLuint randomSpeedAttr,
                     GLuint randomRadiusAttr,
                     GLuint deltaAttr,
                     GLuint colorStartAttr,
                     GLuint colorEndAttr,
                     GLuint sizeUniform,
                     GLuint totalDeltaSpeedUniform) : m_nCount(count),
                                                      m_nProgramID(programId),
                                                      m_nTextureId(textureId),
                                                      m_nRandomPositionAttr(randomPositionAttr),
                                                      m_nRandomSpeedAttr(randomSpeedAttr),
                                                      m_nRandomRadiusAttr(randomRadiusAttr),
                                                      m_nDeltaAttr(deltaAttr),
                                                      m_nColorStartAttr(colorStartAttr),
                                                      m_nColorEndAttr(colorEndAttr),
                                                      m_nSizeUniform(sizeUniform),
                                                      m_nTotalDeltaSpeedUniform(totalDeltaSpeedUniform)
{
    LOGI("Particles::Particles()");
    m_bIsVisible = true;
    m_nTotalDeltaSpeed = 0.0f;
    m_nDeltaSpeed = 0.01f;
    m_fPointSize = 7.0f;
    initArrays();
}

Particles::~Particles() {
    LOGI("Particles::~Particles()");
    deleteObjects();
}

void Particles::render() {
    // Need draw this object?
    if (!m_bIsVisible) {
        return;
    }

    setValues();

    // Use render shader program
    glUseProgram(m_nProgramID);
    checkGLError("Particles - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, m_nTextureId);
    checkGLError("Particles - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(m_nRandomPositionAttr, 2, GL_FLOAT, GL_FALSE, 0, m_pRandomArrayCoords);
    checkGLError("Particles - glVertexAttribPointer - m_nRandomPositionAttr");
    glEnableVertexAttribArray(m_nRandomPositionAttr);
    checkGLError("Particles - glVertexAttribPointer - m_nRandomPositionAttr - enabled");

    // Speed
    glVertexAttribPointer(m_nRandomSpeedAttr, 1, GL_FLOAT, GL_FALSE, 0, m_pRandomArraySpeed);
    checkGLError("Particles - glVertexAttribPointer - m_nRandomSpeedAttr");
    glEnableVertexAttribArray(m_nRandomSpeedAttr);
    checkGLError("Particles - glVertexAttribPointer - m_nRandomSpeedAttr - enabled");

    // Radius
    glVertexAttribPointer(m_nRandomRadiusAttr, 1, GL_FLOAT, GL_FALSE, 0, m_pRandomArrayRadius);
    checkGLError("Particles - glVertexAttribPointer - m_nRandomRadiusAttr");
    glEnableVertexAttribArray(m_nRandomRadiusAttr);
    checkGLError("Particles - glVertexAttribPointer - m_nRandomRadiusAttr - enabled");

    // Delta
    glVertexAttribPointer(m_nDeltaAttr, 1, GL_FLOAT, GL_FALSE, 0, m_pRandomArrayDelta);
    checkGLError("Particles - glVertexAttribPointer - m_nDeltaAttr");
    glEnableVertexAttribArray(m_nDeltaAttr);
    checkGLError("Particles - glVertexAttribPointer - m_nDeltaAttr - enabled");

    // Color start
    glVertexAttribPointer(m_nColorStartAttr, 4, GL_FLOAT, GL_FALSE, 0, m_pColorStartArray);
    checkGLError("Particles - glVertexAttribPointer - m_nColorStartAttr");
    glEnableVertexAttribArray(m_nColorStartAttr);
    checkGLError("Particles - glVertexAttribPointer - m_nColorStartAttr - enabled");

    // Color end
    glVertexAttribPointer(m_nColorEndAttr, 4, GL_FLOAT, GL_FALSE, 0, m_pColorEndArray);
    checkGLError("Particles - glVertexAttribPointer - m_nColorEndAttr");
    glEnableVertexAttribArray(m_nColorEndAttr);
    checkGLError("Particles - glVertexAttribPointer - m_nColorEndAttr - enabled");

    // Size
    glUniform2f(m_nSizeUniform, m_pSizeUniformArray[0], m_pSizeUniformArray[1]);
    checkGLError("Particles - glUniform2f - m_nSizeUniform");

    // Total m_pSingleSpeed
    glUniform1f(m_nTotalDeltaSpeedUniform, m_nTotalDeltaSpeed);
    checkGLError("Particles - glUniform2f - m_nTotalDeltaSpeedUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, m_nCount);
    checkGLError("Particles - glDrawArrays");
}

void Particles::initArrays() {
    // Two point * count
    m_pPositionArray = new GLfloat[m_nCount * 2];
    Methods::fillArray(m_pPositionArray, 0.0f, m_nCount * 2);

    // 4 color * count
    m_pColorStartArray = new GLfloat[m_nCount * 4];
    Methods::fillArray(m_pColorStartArray, 0.0f, m_nCount * 4);

    // 4 color * count
    m_pColorEndArray = new GLfloat[m_nCount * 4];
    Methods::fillArray(m_pColorEndArray, 0.0f, m_nCount * 4);

    // delta * count
    m_pSizeUniformArray = new GLfloat[2];
    m_pSizeUniformArray[0] = 2.0f;
    m_pSizeUniformArray[1] = m_fPointSize;

    // Random coords
    m_pRandomArrayCoords = new GLfloat[m_nCount * 2];
    for(int i = 0; i < m_nCount * 2; i++) {
        m_pRandomArrayCoords[i] = Methods::getFullRandom() * 1.1f;
    }

    // Random radius
    m_pRandomArrayRadius = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++) {
        m_pRandomArrayRadius[i] = Methods::getShortRandom();
    }

    // Random m_pSingleSpeed
    m_pRandomArraySpeed = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++) {
        m_pRandomArraySpeed[i] = Methods::getShortRandom() * 0.5f;
    }

    // Random delta
    m_pRandomArrayDelta = new GLfloat[m_nCount];
    for(int i = 0; i < m_nCount; i++) {
        m_pRandomArrayDelta[i] = Methods::getShortRandom();
    }
}

void Particles::setValues() {
    if (m_nTotalDeltaSpeed > 1000.0f || m_nTotalDeltaSpeed < 0.0f) {
        m_nDeltaSpeed *= -1.0f;
    }

    m_nTotalDeltaSpeed = m_nTotalDeltaSpeed + m_nDeltaSpeed;

    for(int i = 0; i < m_nCount; i++) {
        // Color start
        m_pColorStartArray[i * 4] = Methods::getShortRandom() * 0.5f;
        m_pColorStartArray[i * 4 + 1] = Methods::getShortRandom() * 0.5f;
        m_pColorStartArray[i * 4 + 2] = Methods::getShortRandom() * 0.5f;
        m_pColorStartArray[i * 4 + 3] = 0.3f;

        // Color end
        m_pColorEndArray[i * 4] = Methods::getShortRandom() + 0.5f;
        m_pColorEndArray[i * 4 + 1] = Methods::getShortRandom() + 0.5f;
        m_pColorEndArray[i * 4 + 2] = Methods::getShortRandom() + 0.5f;
        m_pColorEndArray[i * 4 + 3] = 0.95f;
    }
}

void Particles::setSettings() {
    deleteObjects();
    initArrays();
}

void Particles::deleteObjects() {
    delete [] m_pPositionArray;
    delete [] m_pColorStartArray;
    delete [] m_pColorEndArray;
    delete [] m_pSizeUniformArray;
    delete [] m_pRandomArrayCoords;
    delete [] m_pRandomArrayRadius;
    delete [] m_pRandomArraySpeed;
    delete [] m_pRandomArrayDelta;
}

void Particles::setParticlesSize(GLfloat size) {
    m_fPointSize = size > 2.0f && size < 100.0f ? size : m_fPointSize;
}

void Particles::setParticlesCount(GLuint count) {
    m_nCount = count > 1000 && count < 5000 ? count : m_nCount;
}

