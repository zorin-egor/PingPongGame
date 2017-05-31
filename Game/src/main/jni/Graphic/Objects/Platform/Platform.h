#ifndef GAME_PINGPONG_PLATFORM_H
#define GAME_PINGPONG_PLATFORM_H

#include "Graphic/Objects/Object.h"
#include "Common/Methods.h"
#include "Common/Intersect.h"
#include "Common/Structures.h"

class Platform : public Object {

    public:

        static const enum REBOUND_AREA {NONE = 0, LAST_LEFT = 1, LEFT = 2, CENTER = 3, RIGHT = 4, LAST_RIGHT = 5};

        Platform(float _step,
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
                score = 0;
            }

    virtual ~Platform(){
        LOGI("~Platform");
    }

    int getScore() const {
        return score;
    }

    void setScore() {
        ++score;
    }

    void clearScore() {
        score = 0;
    }

    Object::CROSS_SIDE collision(Object * object);
    REBOUND_AREA getRebound(float x, float y, float width);

    private:
        int score;
};


#endif //GAME_PINGPONG_PLATFORM_H
