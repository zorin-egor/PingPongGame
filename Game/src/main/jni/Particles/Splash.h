
#ifndef GAME_PINGPONG_SPLASH_H
#define GAME_PINGPONG_SPLASH_H


#include <GLES2/gl2.h>
#include "AbstractClasses/Render.h"
#include "Common/LogGL.h"
#include "Common/Methods.h"

class Splash : public Render {

    public:
        Splash(GLuint _count,
               GLuint _lifeTime,
               GLuint _programID,
               GLuint _textureID,
               GLuint _positionAttr,
               GLuint _colorStartAttr,
               GLuint _colorEndAttr,
               GLuint _deltaAttr,
               GLuint _sizeUniform ) :  count(_count),
                                        lifeTime(_lifeTime),
                                        programID(_programID),
                                        textureID(_textureID),
                                        positionAttr(_positionAttr),
                                        colorStartAttr(_colorStartAttr),
                                        colorEndAttr(_colorEndAttr),
                                        deltaAttr(_deltaAttr),
                                        sizeUniform(_sizeUniform),
                                        TOTAL_LIFE_TIME(_lifeTime)
        {
            isVisible = true;
            initArrays();
            setSplashPosition(0.0f, 0.0f);
        }

    void initArrays();
    void render();
    void setSplashPosition(GLfloat _x, GLfloat _y);

    void setVisible(bool _isVisible){
        isVisible = _isVisible;
    }

    bool getVisible(){
        return isVisible;
    }

    void setParticlesCount(GLuint _count){
        count = _count > 0 && _count < 5000? _count : count;
    }

    virtual ~Splash(){
        LOGI("~Splash");
        delete [] positionArray;
        delete [] colorStartArray;
        delete [] colorEndArray;
        delete [] deltaArray;
        delete [] sizeArray;
    }

    private:
        void setValues();

        bool isVisible;

        const GLuint TOTAL_LIFE_TIME;
        GLuint count;
        GLint lifeTime;

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

        GLfloat * dxArray;
        GLfloat * dyArray;
};


#endif //GAME_PINGPONG_SPLASH_H
