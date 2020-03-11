#ifndef GAME_PINGPONG_OBJECT_H
#define GAME_PINGPONG_OBJECT_H

#include "Common/Structures.h"
#include "Graphic/View.h"

class Object : public View {

    public:

        static const enum CROSS_SIDE {
            NONE = 0,
            LEFT = 1,
            DOWN = 2,
            RIGHT = 3,
            UP = 4
        };


    protected:

        // Points of cross. Any cross has 4 points.
        std::vector<GLfloat> m_oCrossPoints;

        // Object position
        float m_fWidth;
        float m_fHeight;
        float m_fX;
        float m_fY;
        float m_fDX;
        float m_fDY;
        float m_fStep;

        GLfloat * m_fDefaultCoords;


    public:

        Object(float step,
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

        virtual ~Object();


    public:

        void setDefaultPosition();

        void move();

        void moveY(GLfloat y);

        void moveX(GLfloat x);

        virtual CROSS_SIDE collision(Object * object) = 0;


    public:

        float getWidth() const {
            return m_fWidth;
        }

        float getHeight() const {
            return m_fHeight;
        }

        void setStep(float step) {
            m_fStep = step;
        }

        float getStep() {
            return m_fStep;
        }

        float getDx() const {
            return m_fDX;
        }

        void setDx(float dx) {
            m_fDX = dx;
        }

        float getDy() const {
            return m_fDY;
        }

        void setDy(float dy) {
            m_fDY = dy;
        }

        std::vector<GLfloat> * getCrossPoints() {
            return &m_oCrossPoints;
        }

};


#endif
