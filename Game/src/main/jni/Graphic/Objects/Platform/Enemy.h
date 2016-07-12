#ifndef GAME_PINGPONG_BOT_H
#define GAME_PINGPONG_BOT_H

#include "Common/Structures.h"
#include "Graphic/Objects/Ball/Ball.h"
#include "Graphic/Objects/Platform/Platform.h"

class Enemy : public Platform{

    public:
        Enemy(float _step,
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
              GLfloat * _matrixCoords) : Platform( _step,
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
                dX = 0;
                setCrossHorizont(_verticesCoords);
        }

        void collision(Ball * ball);

        virtual ~Enemy(){
            delete [] crossHorizonArray;
        }

    private:
        void setCrossHorizont(GLfloat * _crossHorizontArray);
        Line<GLfloat> crossHorizonLine;
        GLfloat * crossHorizonArray;
};


#endif //GAME_PINGPONG_BOT_H
