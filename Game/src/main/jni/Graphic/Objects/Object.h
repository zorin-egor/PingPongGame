#ifndef GAME_PINGPONG_OBJECT_H
#define GAME_PINGPONG_OBJECT_H


#include <Common/Structures.h>
#include "Graphic/View.h"

class Object : public View {

    public:
        Object(float _x,
               float _y,
               float _width,
               float _height,
               GLuint _textureID,
               GLuint _programID,
               GLint _positionAttr,
               GLint _textureAttr,
               GLint _transformationAttr,
               GLfloat * _verticesCoords,
               GLfloat * _textureCoords,
               GLfloat * _matrixCoords) : View( _textureID,
                                                _programID,
                                                _positionAttr,
                                                _textureAttr,
                                                _transformationAttr,
                                                Matrix::setVerticesCoords(x, y, width, height, _verticesCoords),
                                                _textureCoords,
                                                _matrixCoords ),
                                          x(_x),
                                          y(_y),
                                          width(_width),
                                          height(_height)
        {

        }

    bool isObjectsInteract(Object * A, Object * B);

    private:

            // Object position
            float width, height;
            float x, y;

};


#endif //GAME_PINGPONG_OBJECT_H
