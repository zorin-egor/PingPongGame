#ifndef GAME_PINGPONG_SHAPE_H
#define GAME_PINGPONG_SHAPE_H

#include <GLES2/gl2.h>
#include <math.h>
#include "AbstractClasses/Render.h"
#include "Common/LogGL.h"
#include "Common/Methods.h"

class Shape : public Render {
    public:
        Shape(  GLuint _count,
                GLfloat _centerX,
                GLfloat _centerY,
                GLfloat _radiusX,
                GLfloat _radiusY,
                GLuint _programID,
                GLuint _textureID,
                GLuint _starsAngle,
                GLuint _starColor,
                GLuint _starCenter,
                GLuint _starRadius,
                GLuint _starArguments,
                GLuint _starSize,
                GLuint _starTotalDeltaSpeed) : count(_count),
                                               centerX(_centerX),
                                               centerY(_centerY),
                                               radiusX(_radiusX),
                                               radiusY(_radiusY),
                                               programID(_programID),
                                               textureID(_textureID),
                                               starsAngle(_starsAngle),
                                               starColor(_starColor),
                                               starCenter(_starCenter),
                                               starRadius(_starRadius),
                                               starArguments(_starArguments),
                                               starSize(_starSize),
                                               starTotalDeltaSpeed(_starTotalDeltaSpeed),
                                               STRICT_SPEED_MAX(10000.0f),
                                               STRICT_SPEED_MIN(0.0f),
                                               pointSize(10.0f)
    {
        LOGI("Graphic::Graphic()");
        isVisible = true;
        init();
    }

    virtual ~Shape(){
        LOGI("Graphic::~Graphic()");
        // Off attributes
        //glDisableVertexAttribArray(starsAngle);
        //glDisableVertexAttribArray(starColor);
        delete [] arrayPosition;
        delete [] arrayColor;
    }

    void render();
    void setSettings();

    void setVisible(bool _isVisible){
        isVisible = _isVisible;
    }

    void setParticlesSize(GLfloat _size){
        pointSize = _size > 0 && _size < 100 ? _size : pointSize;
    }

    void setParticlesCount(GLuint _count){
        count = _count > 5000 && _count < 50000? _count : count;
    }

    bool getVisible(){
        return isVisible;
    }

private:

    void init();
    void setValues();

    // For shader
    const GLuint textureID;
    const GLuint programID;
    const GLuint starsAngle;
    const GLuint starColor;
    const GLuint starCenter;
    const GLuint starRadius;
    const GLuint starArguments;
    const GLuint starSize;
    const GLuint starTotalDeltaSpeed;

    // For data
    GLuint count;
    static const GLuint SIZE_ARRAYS = 4;
    const GLfloat centerX;
    const GLfloat centerY;
    const GLfloat radiusX;
    const GLfloat radiusY;

    // For intervals strict
    const GLfloat STRICT_SPEED_MAX;
    const GLfloat STRICT_SPEED_MIN;
    static const GLfloat STATIC_FIGURES[20][4];

    // For dynamic change
    GLfloat arguments[SIZE_ARRAYS];
    GLfloat * arrayColor;
    GLfloat * arrayPosition;
    GLfloat totalDeltaSpeed;
    GLfloat dParticlesSpeed;
    GLfloat pointSize;

    // For visibility
    bool isVisible;
};

#endif
