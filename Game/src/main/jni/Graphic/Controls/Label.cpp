#include "Label.h"

void  Label::init(){
    if(number.length() > 0){
        width_one = width / (float)number.length();

        for(unsigned int i = 0; i < number.length(); i++){
            char symbol = number.at(i);
            int position = atoi(&symbol);

            GLfloat * textureCoord = Matrix::setTextureCoords(matrix->getDefaultTextureCoord(), 4, 4, position);
            if(isInverse)
                Matrix::rotateTextureCoord(textureCoord, 2);

            View * partOfLabel = new View(textureID,
                                          programID,
                                          positionAttr,
                                          textureAttr,
                                          transformationAttr,
                                          Matrix::setVerticesCoords(x + width_one * (float)i, y, width_one, height, matrix->getDefaultVerticesCoords()),
                                          textureCoord,
                                          matrix->getDefaultMatrix4x4());
            labelLinks.push_back(partOfLabel);
        }
    }
}

void Label::setNumber(std::string _number){
    number = _number;
    if(isInverse)
        std::reverse(_number.begin(), _number.end());

    for(int i = 0; i < labelLinks.size(); i++){
        char symbol = number.at(i);
        int position = atoi(&symbol);
        Matrix::setTextureCoords(labelLinks.at(i)->getTextureCoordinates(), 4, 4, position);
        if(isInverse)
            Matrix::rotateTextureCoord(labelLinks.at(i)->getTextureCoordinates(), 2);
    }
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