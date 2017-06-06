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
                                               pointSize(10.0f),
                                               COLOR_EQUALS_PARTS(0.5f),
                                               COLOR_INITIAL_TIMER(10)
    {
        LOGI("Shape::Shape()");
        isVisible = true;
        isColorReset = false;
        colorParts = COLOR_EQUALS_PARTS;
        colorResetTimer = COLOR_INITIAL_TIMER;
        initArrays();
    }

    virtual ~Shape(){
        LOGI("~Shape");
        // Off attributes
        //glDisableVertexAttribArray(starsAngle);
        //glDisableVertexAttribArray(starColor);
        deleteObjects();
    }

    void render();
    void setSettings();
    void setColor();
    void setColorLight();
    void setColorPart(GLuint first, GLuint second);
    void setColorTimer();
    void setParticlesSize(GLfloat _size);
    void setParticlesCount(GLuint _count);
    void deleteObjects();

    void setVisible(bool _isVisible){
        isVisible = _isVisible;
    }

    bool getVisible(){
        return isVisible;
    }

private:

    void initArrays();
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
    static const GLfloat STATIC_FIGURES[30][4];

    // For dynamic change
    GLfloat arguments[SIZE_ARRAYS];
    GLfloat * arrayColor;
    GLfloat * arrayPosition;
    GLfloat totalDeltaSpeed;
    GLfloat dParticlesSpeed;
    GLfloat pointSize;

    // For visibility
    bool isVisible;

    // Color reset
    bool isColorReset;
    GLint colorResetTimer;
    GLfloat colorParts;
    const GLfloat COLOR_EQUALS_PARTS;
    const GLint COLOR_INITIAL_TIMER;
};

#endif
