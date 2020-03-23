#ifndef BALL_H
#define BALL_H

#include <typeinfo>
#include <queue>
#include <Particles/Splash.h>

#include "../../../Common/Intersect.h"
#include "../../../Common/Structures.h"
#include "../Platform/Platform.h"
#include "../Object.h"

class Ball : public Object {

    private:

        const float DX_MIN;
        const float DX_MAX;
        const float INCREASE_SPEED_TO;
        const float DELTA_SPEED;
        const float DEFAULT_SPEED;

        Splash * m_pSplash;
        std::queue<GLfloat> m_pLastPoint;
        std::queue<GLfloat> m_pPlumePoints;

        float m_fSign;
        int m_nSpeed;
        bool m_bIsOut;


    public:

        Ball(float step,
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
             GLfloat * matrixCoords,
             Splash * splash);

        virtual ~Ball();


    public:

        Object::CROSS_SIDE collision(Object * object);

        bool collision(Platform * object);

        bool getIsOut() const {
            return m_bIsOut;
        }

        void setIsOut(bool isOut) {
            Ball::m_bIsOut = isOut;
        }

        int getSpeed() {
            return m_nSpeed;
        }

        void resetSpeed() {
            m_fDY = DEFAULT_SPEED;
            m_nSpeed = 0;
        }

        std::queue<GLfloat> * getLastPoint() {
            return &m_pLastPoint;
        }

        std::queue<GLfloat> * getPlumePoints() {
            return &m_pPlumePoints;
        }


    private:

        void setPreviousPoint();

        void setQueuePointsForPlume();

        Object::CROSS_SIDE collisionLeftRightWall(Object * object);

        Object::CROSS_SIDE collisionUpDownWall(Object * object);

        void increaseSpeed();
};


#endif
