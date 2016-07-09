#ifndef GAME_PINGPONG_BALL_H
#define GAME_PINGPONG_BALL_H

#include <typeinfo>
#include <queue>
#include <Particles/Splash.h>

#include "Graphic/Objects/Platform/Platform.h"
#include "Graphic/Objects/Object.h"
#include "Common/Intersect.h"
#include "Common/Structures.h"

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
             GLfloat * _matrixCoords,
             Splash * _splash) : Object( _step,
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

                                        splash(_splash),
                                        DX_MAX(0.06f),
                                        DX_MIN(0.03),
                                        INCREASE_SPEED_TO(_height),
                                        DELTA_SPEED(0.00001f)
        {
                setDy(Methods::getRandSign() * _step);
                isOut = false;
                sign = 1.0f;
        }

        bool collision(Object * object);
        bool collision(Platform * object);

        bool getIsOut() const {
            return isOut;
        }

        void setIsOut(bool isOut) {
            Ball::isOut = isOut;
        }

        std::queue<GLfloat> * getLastPoint(){
            return &lastPoint;
        }

        std::queue<GLfloat> * getPlumePoints(){
            return &plumePoints;
        }

    private:

        void setPreviousPoint();
        void setQueuePointsForPlume();

        Splash * splash;
        std::queue<GLfloat> lastPoint;
        std::queue<GLfloat> plumePoints;

        const float DX_MIN;
        const float DX_MAX;
        const float INCREASE_SPEED_TO;
        const float DELTA_SPEED;

        float sign;

        bool isOut;
        bool collisionLeftRightWall(Object * object);
        bool collisionUpDownWall(Object * object);
        void increaseSpeed();
};


#endif //GAME_PINGPONG_BALL_H
