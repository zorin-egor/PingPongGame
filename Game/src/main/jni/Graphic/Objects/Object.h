#ifndef GAME_PINGPONG_OBJECT_H
#define GAME_PINGPONG_OBJECT_H


#include "Graphic/View.h"

class Object : public View {

    public:
        Object(bool _isUpButton,
               float _x,
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
                                                _verticesCoords,
                                                _textureCoords,
                                                _matrixCoords )
        {



        }


    private:

};


#endif //GAME_PINGPONG_OBJECT_H
