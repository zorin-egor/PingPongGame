#include "Plume.h"

void Plume::render() {
    // Need draw this object?
    if(!isVisible)
        return;

    setValues();

    // Use render shader programm
    glUseProgram(programID);
    checkGLError("Plume - glUseProgram");

    // Choose you texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    checkGLError("Plume - glBindTexture");

    // Fill attributes and uniforms
    // Position
    glVertexAttribPointer(positionAttr, 2, GL_FLOAT, GL_FALSE, 0, positionArray);
    checkGLError("Plume - glVertexAttribPointer - positionAttr");
    glEnableVertexAttribArray(positionAttr);
    checkGLError("Plume - glVertexAttribPointer - positionAttr - enabled");

    // Color start
    glVertexAttribPointer(colorStartAttr, 4, GL_FLOAT, GL_FALSE, 0, colorStartArray);
    checkGLError("Plume - glVertexAttribPointer - colorStartAttr");
    glEnableVertexAttribArray(colorStartAttr);
    checkGLError("Plume - glVertexAttribPointer - colorStartAttr - enabled");

    // Color end
    glVertexAttribPointer(colorEndAttr, 4, GL_FLOAT, GL_FALSE, 0, colorEndArray);
    checkGLError("Plume - glVertexAttribPointer - colorEndAttr");
    glEnableVertexAttribArray(colorEndAttr);
    checkGLError("Plume - glVertexAttribPointer - colorEndAttr - enabled");

    // Delta singleSpeed
    glVertexAttribPointer(deltaAttr, 1, GL_FLOAT, GL_FALSE, 0, deltaArray);
    checkGLError("Plume - glVertexAttribPointer - deltaAttr");
    glEnableVertexAttribArray(deltaAttr);
    checkGLError("Plume - glVertexAttribPointer - deltaAttr - enabled");

    // Size
    glUniform2f(sizeUniform, sizeArray[0], sizeArray[1]);
    checkGLError("Plume - glUniform2f - sizeUniform");

    // Draw poligon
    glDrawArrays(GL_POINTS, 0, count);
    checkGLError("Plume - glDrawArrays");
}

void Plume::initArrays(){

    // Two point * count
    positionArray = new GLfloat[MAX_COUNT * 2];
    Methods::fillArray(positionArray, 0.0f, MAX_COUNT * 2);

    // Delta array for mix
    deltaArray = new GLfloat[MAX_COUNT];
    for(int i = 0; i < MAX_COUNT; i++){
        deltaArray[i] = Methods::getShortRandom() * 0.9;
    }

    // 4 color * count
    colorStartArray = new GLfloat[MAX_COUNT * 4];
    Methods::fillArray(colorStartArray, 0.0f, MAX_COUNT * 4);

    // 4 color * count
    colorEndArray = new GLfloat[MAX_COUNT * 4];
    Methods::fillArray(colorEndArray, 0.0f, MAX_COUNT * 4);

    // Points size
    sizeArray = new GLfloat[2];
    sizeArray[0] = MIN_SIZE;
    sizeArray[1] = MAX_SIZE;
}

void Plume::setValues(){
    for(int i = 0; i < MAX_COUNT; i++){
        // Color start
        colorStartArray[i * 4] = Methods::getShortRandom() * 0.5f;
        colorStartArray[i * 4 + 1] = Methods::getShortRandom() * 0.5f;
        colorStartArray[i * 4 + 2] = Methods::getShortRandom() * 0.5f;
        colorStartArray[i * 4 + 3] = 0.1f;

        // Color end
        colorEndArray[i * 4] = Methods::getShortRandom() + 0.5f;
        colorEndArray[i * 4 + 1] = Methods::getShortRandom() + 0.5f;
        colorEndArray[i * 4 + 2] = Methods::getShortRandom() + 0.5f;
    }
}

void Plume::setPlumePoints(std::queue<GLfloat> * points){
    if(points->size() > 0 && points->size() < MAX_COUNT && points->size() % 2 == 0){
        std::queue<GLfloat> plumePoints(*points);
        unsigned int halfQueue = points->size() / 2;
        unsigned int pointsPerStep = MAX_COUNT / halfQueue;
        count = pointsPerStep * halfQueue;
        unsigned int i = 0;
        float dispersion = 0.008f;
        float alpha = 0.005f;

        while(plumePoints.size() > 0){
            GLfloat x = plumePoints.front();
            plumePoints.pop();
            GLfloat y = plumePoints.front();
            plumePoints.pop();

            for(int j = 0; j < pointsPerStep; j++, i++){
                // Set plume position
                positionArray[i * 2] = x + Methods::getFullRandom() * dispersion;
                positionArray[i * 2 + 1] = y + Methods::getFullRandom() * dispersion;

                // Set alpha of tale
                colorEndArray[i * 4 + 3] = alpha;
            }

            dispersion += 0.002f;
            alpha += 0.05f;
        }
    }
}