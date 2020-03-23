#ifndef ENEMY_H
#define ENEMY_H

#include "../../../Common/Structures.h"
#include "../Ball/Ball.h"
#include "../Platform/Platform.h"

class Enemy : public Platform {

    private:

        Line<GLfloat> m_oCrossHorizonLine;
        GLfloat * m_pCrossHorizonArray;


    public:

        Enemy(float step,
              float x,
              float y,
              float width,
              float height,
              GLuint textureID,
              GLuint programID,
              GLint positionAttr,
              GLint textureAttr,
              GLint transformationAttr,
              GLfloat * verticesCoords,
              GLfloat * textureCoords,
              GLfloat * matrixCoords);

        virtual ~Enemy();


    public:

        void collision(Ball * ball);


    private:

        void setCrossHorizon(GLfloat * crossHorizonArray);
};


#endif
