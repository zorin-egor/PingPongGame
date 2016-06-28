#ifndef GAME_PINGPONG_PARTICLES_H
#define GAME_PINGPONG_PARTICLES_H

#include <GLES2/gl2.h>
#include <cmath>

#include "AbstractClasses/Render.h"
#include "Common/LogGL.h"

class Particles : public Render{

    public:
        Particles(unsigned int _count,
                  GLuint _programID,
                  GLuint _textureID,
                  GLuint _positionAttr,
                  GLuint _deltaAttr,
                  GLuint _colorStartAttr,
                  GLuint _colorEndAttr,
                  GLuint _sizeUniform) :
                count(_count),
                textureID(_textureID),
                programID(_programID),
                positionAttr(_positionAttr),
                deltaAttr(_deltaAttr),
                colorStartAttr(_colorStartAttr),
                colorEndAttr(_colorEndAttr),
                sizeUniform(_sizeUniform)

        {
            isVisible = true;
            totalDeltaSpeed = 0.0f;
            deltaSpeed = 0.01f;
            initArrays();
        }

        virtual ~Particles(){
            delete [] positionArray;
            delete [] deltaArray;
            delete [] colorStartArray;
            delete [] colorEndArray;
            delete [] sizeUniformArray;
            delete [] randomArrayCoords;
            delete [] randomArrayRadius;
            delete [] randomArraySpeed;
            delete [] randomArrayDelta;
        }

        void render();

        void setVisible(bool _isVisible){
            isVisible = _isVisible;
        }

        bool getVisible(){
            return isVisible;
        }

    private:

        void initArrays();
        void setValues();

        GLuint textureID;
        GLuint programID;

        GLint positionAttr;
        GLint deltaAttr;
        GLint colorStartAttr;
        GLint colorEndAttr;
        GLint sizeUniform;

        GLfloat * positionArray;
        GLfloat * deltaArray;
        GLfloat * colorStartArray;
        GLfloat * colorEndArray;
        GLfloat * sizeUniformArray;

        GLfloat * randomArrayCoords;
        GLfloat * randomArrayRadius;
        GLfloat * randomArraySpeed;
        GLfloat * randomArrayDelta;

        unsigned int count;
        bool isVisible;

        float totalDeltaSpeed;
        float deltaSpeed;
};


#endif //GAME_PINGPONG_PARTICLES_H
