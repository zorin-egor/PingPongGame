#include "View.h"

View::View (GLuint textureID,
            GLuint programID,
            GLint positionAttr,
            GLint textureAttr,
            GLint transformationAttr,
            GLfloat * polygonCoordinates,
            GLfloat * textureCoordinates,
            GLfloat * transformationMatrix) : m_nTextureId(textureID),
                                              m_nProgramId(programID),
                                              m_nPositionAttr(positionAttr),
                                              m_nTextureAttr(textureAttr),
                                              m_nTransformationAttr(transformationAttr),
                                              m_pPolygonCoordinates(polygonCoordinates),
                                              m_pTextureCoordinates(textureCoordinates),
                                              m_pTransformationMatrix(transformationMatrix)
{
    LOGI("View::View()");
    m_bIsVisible = true;
    m_oRectangle.setRectangle(m_pPolygonCoordinates);
}

View::~View() {
    LOGI("View::~View()");
}

void View::render() {
    // Need draw this object?
    if (!m_bIsVisible) {
        return;
    }

    // Use render shader program
    glUseProgram(m_nProgramId);
    checkGLError("View - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, m_nTextureId);
    checkGLError("View - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(m_nPositionAttr, 2, GL_FLOAT, GL_FALSE, 0, m_pPolygonCoordinates);
    checkGLError("View - glVertexAttribPointer - position");
    glEnableVertexAttribArray(m_nPositionAttr);
    checkGLError("View - glVertexAttribPointer - position - enabled");

    // Texture
    glVertexAttribPointer(m_nTextureAttr, 2, GL_FLOAT, GL_FALSE, 0, m_pTextureCoordinates);
    checkGLError("View - glVertexAttribPointer - texture");
    glEnableVertexAttribArray(m_nTextureAttr);
    checkGLError("View - glVertexAttribPointer - texture - enabled");

    // Transformation
    glUniformMatrix4fv(m_nTransformationAttr, 1, GL_FALSE, m_pTransformationMatrix);
    checkGLError("View - glUniformMatrix4fv");

    // Draw polygon
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    checkGLError("View - glDrawArrays");
}