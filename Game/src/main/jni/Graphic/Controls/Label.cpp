#include "Label.h"

void  Label::init(){
    if(number.length() > 0){
        width_one = width / (float)number.length();

        for(unsigned int i = 0; i < number.length(); i++){
            char symbol = number.at(i);
            int position = atoi(&symbol);

            View * partOfLabel = new View(textureID,
                                          programID,
                                          positionAttr,
                                          textureAttr,
                                          transformationAttr,
                                          getVerticesCoords(x + width_one * (float)i, width_one, matrix->getDefaultVerticesCoords()),
                                          Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 4, 4, position),
                                          matrix->getDefaultMatrix4x4());
            labelLinks.push_back(partOfLabel);
        }
    }
}

GLfloat * Label::getVerticesCoords(float _x, float _width, GLfloat * verticesCoords){

    // Top left
    verticesCoords[0] = _x;
    verticesCoords[1] = y;

    // Bottom left
    verticesCoords[2] = _x;
    verticesCoords[3] = y - height;

    // Bottom right
    verticesCoords[4] = _x + _width;
    verticesCoords[5] = y - height;

    // Top right
    verticesCoords[6] = _x + _width;
    verticesCoords[7] = y;

    return verticesCoords;
}

void Label::setNumber(std::string _number){
    clearLabels();
    number = _number;
    init();
}

void Label::render(){
    for(int i = 0; i < labelLinks.size(); i++){
        labelLinks.at(i)->render();
    }
}

void Label::clearLabels(){
    for(int i = 0; i < labelLinks.size(); i++){
        delete labelLinks.at(i);
    }

    labelLinks.clear();
}