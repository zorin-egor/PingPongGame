
#ifndef GAME_PINGPONG_SPLASH_H
#define GAME_PINGPONG_SPLASH_H


#include <GLES2/gl2.h>
#include "AbstractClasses/Render.h"
#include "Common/LogGL.h"
#include "Common/Methods.h"

class Splash : public Render {

    public:
        Splash(unsigned int _count,
               unsigned int _lifeTime,
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
                                        sizeUniform(_sizeUniform)
        {
            isVisible = true;
            initArrays();
        }

    void render();


    void setSplashPosition(GLfloat _x, GLfloat _y){
        x = _x;
        y = _y;
    }

    void setVisible(bool _isVisible){
        isVisible = _isVisible;
    }

    bool getVisible(){
        return isVisible;
    }

    virtual ~Splash(){
        delete [] positionArray;
        delete [] colorStartArray;
        delete [] colorEndArray;
        delete [] deltaArray;
        delete [] sizeArray;
    }

    private:
        void initArrays();
        void setValues();

        bool isVisible;

        unsigned int count;
        unsigned int lifeTime;

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

        GLfloat x;
        GLfloat y;
};


#endif //GAME_PINGPONG_SPLASH_H
