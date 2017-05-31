#include "View.h"

void View::render(){
    // Need draw this object?
    if(!isVisible)
        return;

    // Use render shader programm
    glUseProgram(programID);
    checkGLError("View - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGLError("View - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(positionAttr, 2, GL_FLOAT, GL_FALSE, 0, polygonCoordinates);
    checkGLError("View - glVertexAttribPointer - position");
    glEnableVertexAttribArray(positionAttr);
    checkGLError("View - glVertexAttribPointer - position - enabled");

    // Texture
    glVertexAttribPointer(textureAttr, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    checkGLError("View - glVertexAttribPointer - texture");
    glEnableVertexAttribArray(textureAttr);
    checkGLError("View - glVertexAttribPointer - texture - enabled");

    // Transformation
    glUniformMatrix4fv(transformationAttr, 1, GL_FALSE, transformationMatrix);
    checkGLError("View - glUniformMatrix4fv");

    // Draw poligon
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    checkGLError("View - glDrawArrays");
}