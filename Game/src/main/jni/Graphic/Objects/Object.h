#ifndef GAME_PINGPONG_OBJECT_H
#define GAME_PINGPONG_OBJECT_H

#include "Common/Structures.h"
#include "Graphic/View.h"

class Object : public View {

    public:
        Object(float _step,
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
                                                Matrix::setVerticesCoords(_x, _y, _width, _height, _verticesCoords),
                                                _textureCoords,
                                                _matrixCoords ),
                                          step(_step),
                                          x(_x),
                                          y(_y),
                                          width(_width),
                                          height(_height)
        {
            dx = 0;
            dy = 0;
        }

    float getWidth() const {
        return width;
    }

    float getHeight() const {
        return height;
    }

    void setStep(float _step) {
        step = _step;
    }

    float getDx() const {
        return dx;
    }

    void setDx(float _dx) {
        dx = _dx;
    }

    float getDy() const {
        return dy;
    }

    void setDy(float _dy) {
        dy = _dy;
    }

    std::vector<GLfloat> * getCrossPoints() {
        return &crossPoints;
    }

    void move();
    virtual bool collision(Object * object) = 0;

    virtual ~Object(){

    }

private:
        // Points of cross. Any cross has 4 points.
        std::vector<GLfloat> crossPoints;

        // Object position
        float width, height;
        float x, y;
        float dx, dy;
        float step;

        // Play field
        GLfloat * field;
};


#endif //GAME_PINGPONG_OBJECT_H
