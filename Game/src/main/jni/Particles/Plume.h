#ifndef GAME_PINGPONG_PLUME_H
#define GAME_PINGPONG_PLUME_H

#include <queue>
#include "Splash.h"

class Plume : public Render {

    public:
        Plume(unsigned int _count,
               GLuint _programID,
               GLuint _textureID,
               GLuint _positionAttr,
               GLuint _colorStartAttr,
               GLuint _colorEndAttr,
               GLuint _deltaAttr,
               GLuint _sizeUniform ) : currentCount(_count),
                                       programID(_programID),
                                       textureID(_textureID),
                                       positionAttr(_positionAttr),
                                       colorStartAttr(_colorStartAttr),
                                       colorEndAttr(_colorEndAttr),
                                       deltaAttr(_deltaAttr),
                                       sizeUniform(_sizeUniform),
                                       MAX_COUNT(_count)
        {
            isVisible = true;
            initArrays();
        }

    void render();

    void setVisible(bool _isVisible){
        isVisible = _isVisible;
    }

    bool getVisible(){
        return isVisible;
    }

    void setPlumePoints(std::queue<GLfloat> * points);

    virtual ~Plume(){
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
        unsigned int currentCount;
        const unsigned int MAX_COUNT;

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
