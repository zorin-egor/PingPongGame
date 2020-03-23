#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../../Common/Methods.h"
#include "../../../Common/Intersect.h"
#include "../../../Common/Structures.h"
#include "../Object.h"

class Platform : public Object {

    public:

        static const enum REBOUND_AREA {
            NONE = 0,
            LAST_LEFT = 1,
            LEFT = 2,
            CENTER = 3,
            RIGHT = 4,
            LAST_RIGHT = 5
        };


    private:

        int m_nScore;


    public:

        Platform(float step,
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

        virtual ~Platform();


    public:

        int getScore() const {
            return m_nScore;
        }

        void setScore() {
            ++m_nScore;
        }

        void clearScore() {
            m_nScore = 0;
        }

        Object::CROSS_SIDE collision(Object * object);

        REBOUND_AREA getRebound(float x, float y, float width);

};


#endif
