#include "Object.h"

Object::Object(float step,
               float x,
               float y,
               float width,
               float height,
               GLuint textureID,
               GLuint programID,
               GLint positionAttr,
               GLint textureAttr,
               GLint transformationAttr,
               GLfloat * verticesCoords,
               GLfloat * textureCoords,
               GLfloat * matrixCoords) : View(textureID,
                                              programID,
                                              positionAttr,
                                              textureAttr,
                                              transformationAttr,
                                              Matrix::setVerticesCoords(x, y, width, height, verticesCoords),
                                              textureCoords,
                                              matrixCoords ),
                                         m_fStep(step),
                                         m_fX(x),
                                         m_fY(y),
                                         m_fWidth(width),
                                         m_fHeight(height)
{
    LOGI("Object::Object()");
    m_fDX = 0;
    m_fDY = 0;

    m_fDefaultCoords = new GLfloat[8];
    memcpy(m_fDefaultCoords, getPolygonCoordinates(), 8 * sizeof(GLfloat));
}

Object::~Object() {
    LOGI("Object::~Object()");
}

void Object::move() {
    for(int i = 0; i < 4; i++) {
        m_pPolygonCoordinates[i * 2] += m_fDX;
        m_pPolygonCoordinates[i * 2 + 1] += m_fDY;
    }
}

void Object::moveX(GLfloat x) {
    for(int i = 0; i < 4; i++) {
        m_pPolygonCoordinates[i * 2] += x;
    }
}

void Object::moveY(GLfloat y) {
    for(int i = 0; i < 4; i++) {
        m_pPolygonCoordinates[i * 2 + 1] += y;
    }
}

void Object::setDefaultPosition() {
    for(int i = 0; i < 8; i++) {
        m_pPolygonCoordinates[i] = m_fDefaultCoords[i];
    }

    m_fDY *= Methods::getRandSign();
    //m_fDY *= 1.0f;
}