#ifndef GAME_PINGPONG_NUMBERS_H
#define GAME_PINGPONG_NUMBERS_H

#include "AbstractClasses/Render.h"
#include "Common/Methods.h"
#include "Common/Structures.h"
#include "Graphic/View.h"

#include <string>
#include <vector>

class Label {

    public:
        Label(Matrix * _matrix,
              GLuint _textureID,
              GLuint _programID,
              GLint _positionAttr,
              GLint _textureAttr,
              GLint _transformationAttr,
              std::string _number,
              float _x,
              float _y,
              float _width,
              float _height) : matrix(_matrix),
                               textureID(_textureID),
                               programID(_programID),
                               positionAttr(_positionAttr),
                               textureAttr(_textureAttr),
                               transformationAttr(_transformationAttr),
                               number(_number),
                               x(_x),
                               y(_y),
                               width(_width),
                               height(_height)
        {
            init();
        }

        void setNumber(std::string _number);
        void render();
        void clearLabels();

        ~Label(){
            clearLabels();
        };

    private:
        void init();

        Matrix * matrix;

        std::vector<View *> labelLinks;
        std::string number;

        float x;
        float y;
        float width;
        float height;
        float width_one;

        GLuint textureID;
        GLuint programID;
        GLint positionAttr;
        GLint textureAttr;
        GLint transformationAttr;
};

#endif //GAME_PINGPONG_NUMBERS_H
