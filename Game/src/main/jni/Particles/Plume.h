#ifndef GAME_PINGPONG_PLUME_H
#define GAME_PINGPONG_PLUME_H

#include <queue>
#include "Splash.h"

class Plume : public Render {

    public:
        Plume( GLuint _count,
               GLuint _programID,
               GLuint _textureID,
               GLuint _positionAttr,
               GLuint _colorStartAttr,
               GLuint _colorEndAttr,
               GLuint _deltaAttr,
               GLuint _sizeUniform ) : count(_count),
                                       programID(_programID),
                                       textureID(_textureID),
                                       positionAttr(_positionAttr),
                                       colorStartAttr(_colorStartAttr),
                                       colorEndAttr(_colorEndAttr),
                                       deltaAttr(_deltaAttr),
                                       sizeUniform(_sizeUniform),
                                       MAX_COUNT(_count),
                                       MAX_SIZE(7.0f),
                                       MIN_SIZE(4.0f)
        {
            isVisible = true;
            initArrays();
        }

    void initArrays();
    void render();

    void setVisible(bool _isVisible){
        isVisible = _isVisible;
    }

    bool getVisible(){
        return isVisible;
    }

    void setParticlesCount(GLuint _count){
        count = _count > 0 && _count < 500? _count : count;
    }

    void setPlumePoints(std::queue<GLfloat> * points);

    virtual ~Plume(){
        LOGI("~Plume");
        delete [] positionArray;
        delete [] colorStartArray;
        delete [] colorEndArray;
        delete [] deltaArray;
        delete [] sizeArray;
    }

    private:
        void setValues();

        bool isVisible;
        GLuint count;
        const GLuint MAX_COUNT;
        const GLuint MAX_SIZE;
        const GLuint MIN_SIZE;

        GLuint programID;
        GLuint textureID;
        GLuint positionAttr;
        GLuint colorStartAttr;
        GLuint colorEndAttr;
        GLuint deltaAttr;
        GLuint sizeUniform;

        GLfloat * positionArray;
        GLfloat * colorStartArray;
        GLfloat * colorEndArray;
        GLfloat * deltaArray;
        GLfloat * sizeArray;
};

#endif //GAME_PINGPONG_PLUME_H
