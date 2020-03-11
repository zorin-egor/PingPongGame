#ifndef GAME_PINGPONG_BOT_H
#define GAME_PINGPONG_BOT_H

#include "Common/Structures.h"
#include "Graphic/Objects/Ball/Ball.h"
#include "Graphic/Objects/Platform/Platform.h"

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
