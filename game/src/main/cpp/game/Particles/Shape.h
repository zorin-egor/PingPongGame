#ifndef SHAPE_H
#define SHAPE_H

#include <GLES2/gl2.h>
#include <math.h>
#include "../AbstractClasses/Render.h"
#include "../Common/LogGL.h"
#include "../Common/Methods.h"

class Shape : public Render {

    private:

        static const GLuint SIZE_ARRAYS = 4;
        static const GLfloat STATIC_FIGURES[30][4];

        const GLfloat COLOR_EQUALS_PARTS;
        const GLint COLOR_INITIAL_TIMER;

        const GLfloat CENTER_X;
        const GLfloat CENTER_Y;
        const GLfloat RADIUS_X;
        const GLfloat RADIUS_Y;

        const GLfloat STRICT_SPEED_MAX;
        const GLfloat STRICT_SPEED_MIN;

        // For shader
        const GLuint m_nTextureID;
        const GLuint m_nProgramID;
        const GLuint m_nStarsAngle;
        const GLuint m_nStarColor;
        const GLuint m_nStarCenter;
        const GLuint m_nStarRadius;
        const GLuint m_nStarArguments;
        const GLuint m_nStarSize;
        const GLuint m_nStarTotalDeltaSpeed;

        // For data
        GLuint m_nCount;

        // For dynamic change
        GLfloat m_fArguments[SIZE_ARRAYS];
        GLfloat * m_fArrayColor;
        GLfloat * m_fArrayPosition;
        GLfloat m_fTotalDeltaSpeed;
        GLfloat m_fParticlesSpeed;
        GLfloat m_fPointSize;

        // For visibility
        bool m_bIsVisible;

        // Color reset
        bool m_bIsColorReset;
        GLint m_nColorResetTimer;
        GLfloat m_fColorParts;


    public:

        Shape(GLuint count,
              GLfloat centerX,
              GLfloat centerY,
              GLfloat radiusX,
              GLfloat radiusY,
              GLuint programID,
              GLuint textureID,
              GLuint starsAngle,
              GLuint starColor,
              GLuint starCenter,
              GLuint starRadius,
              GLuint starArguments,
              GLuint starSize,
              GLuint starTotalDeltaSpeed);

        virtual ~Shape();


    public:

        void render();

        void setSettings();

        void setColor();

        void setColorLight();

        void setColorPart(GLuint first, GLuint second);

        void setColorTimer();

        void setParticlesSize(GLfloat size);

        void setParticlesCount(GLuint count);

        void deleteObjects();

        void setVisible(bool isVisible) {
            m_bIsVisible = isVisible;
        }

        bool getVisible() {
            return m_bIsVisible;
        }


    private:

        void initArrays();

        void setValues();
};

#endif
