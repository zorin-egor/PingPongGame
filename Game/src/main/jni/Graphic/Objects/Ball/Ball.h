#ifndef GAME_PINGPONG_BALL_H
#define GAME_PINGPONG_BALL_H

#include <typeinfo>
#include <queue>

#include "Graphic/Objects/Platform/Platform.h"
#include "Graphic/Objects/Object.h"
#include "Common/Intersect.h"

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
                                                _matrixCoords ),

                                        DX_MAX(0.05f),
                                        DX_MIN(0.02)
        {
                setDy(_step);
                isOut = false;
        }

        bool collision(Object * object);
        bool collision(Platform * object);

        bool getIsOut() const {
            return isOut;
        }

        void setIsOut(bool isOut) {
            Ball::isOut = isOut;
        }

        std::queue<GLfloat> * getLastPoint() {
            return &lastPoint;
        }

    private:
        std::queue<GLfloat> lastPoint;

        const float DX_MIN;
        const float DX_MAX;

        bool isOut;
        bool collisionLeftRightWall(Object * object);
        bool collisionUpDownWall(Object * object);
};


#endif //GAME_PINGPONG_BALL_H
