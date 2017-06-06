#ifndef GAME_PINGPONG_PARTICLES_H
#define GAME_PINGPONG_PARTICLES_H

#include <GLES2/gl2.h>
#include <cmath>

#include "AbstractClasses/Render.h"
#include "Common/LogGL.h"

class Particles : public Render {

    public:
        Particles(GLuint _count,
                  GLuint _programID,
                  GLuint _textureID,
                  GLuint _randomPositionAttr,
                  GLuint _randomSpeedAttr,
                  GLuint _randomRadiusAttr,
                  GLuint _deltaAttr,
                  GLuint _colorStartAttr,
                  GLuint _colorEndAttr,
                  GLuint _sizeUniform,
                  GLuint _totalDeltaSpeedUniform) :
                count(_count),
                programID(_programID),
                textureID(_textureID),
                randomPositionAttr(_randomPositionAttr),
                randomSpeedAttr(_randomSpeedAttr),
                randomRadiusAttr(_randomRadiusAttr),
                deltaAttr(_deltaAttr),
                colorStartAttr(_colorStartAttr),
                colorEndAttr(_colorEndAttr),
                sizeUniform(_sizeUniform),
                totalDeltaSpeedUniform(_totalDeltaSpeedUniform)
        {
            isVisible = true;
            totalDeltaSpeed = 0.0f;
            deltaSpeed = 0.01f;
            pointSize = 7.0f;
            initArrays();
        }

        virtual ~Particles(){
            LOGI("~Particles");
            deleteObjects();
        }

        void initArrays();
        void setSettings();
        void render();
        void deleteObjects();
        void setParticlesSize(GLfloat _size);
        void setParticlesCount(GLuint _count);

        void setVisible(bool _isVisible){
            isVisible = _isVisible;
        }

        bool getVisible(){
            return isVisible;
        }

    private:

        void setValues();

        GLuint textureID;
        GLuint programID;

        GLuint randomPositionAttr;
        GLuint randomSpeedAttr;
        GLuint randomRadiusAttr;
        GLuint totalDeltaSpeedUniform;
        GLint deltaAttr;
        GLint colorStartAttr;
        GLint colorEndAttr;
        GLint sizeUniform;
        GLfloat pointSize;

        GLfloat * positionArray;
        GLfloat * colorStartArray;
        GLfloat * colorEndArray;
        GLfloat * sizeUniformArray;

        GLfloat * randomArrayCoords;
        GLfloat * randomArrayRadius;
        GLfloat * randomArraySpeed;
        GLfloat * randomArrayDelta;

        GLuint count;
        bool isVisible;

        float totalDeltaSpeed;
        float deltaSpeed;
};


#endif //GAME_PINGPONG_PARTICLES_H
