#ifndef GAME_PINGPONG_BALL_H
#define GAME_PINGPONG_BALL_H


#include "Graphic/Objects/Object.h"

class Ball : public Object {

    public:
        Ball(float _step,
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
             GLfloat * _matrixCoords) : Object( _step,
                                                _x,
                                                _y,
                                                _width,
                                                _height,
                                                _textureID,
                                                _programID,
                                                _positionAttr,
                                                _textureAttr,
                                                _transformationAttr,
                                                _verticesCoords,
                                                _textureCoords,
                                                _matrixCoords )
        {

        }

    bool collision(Object object);
    void move();

    private:


};


#endif //GAME_PINGPONG_BALL_H
