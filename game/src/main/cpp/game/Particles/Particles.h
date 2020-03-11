#ifndef PARTICLES_H
#define PARTICLES_H

#include <GLES2/gl2.h>
#include <cmath>

#include "AbstractClasses/Render.h"
#include "Common/LogGL.h"

class Particles : public Render {

    private:

        GLuint m_nTextureId;
        GLuint m_nProgramID;

        GLuint m_nRandomPositionAttr;
        GLuint m_nRandomSpeedAttr;
        GLuint m_nRandomRadiusAttr;
        GLuint m_nTotalDeltaSpeedUniform;
        GLint m_nDeltaAttr;
        GLint m_nColorStartAttr;
        GLint m_nColorEndAttr;
        GLint m_nSizeUniform;
        GLfloat m_fPointSize;

        GLfloat * m_pPositionArray;
        GLfloat * m_pColorStartArray;
        GLfloat * m_pColorEndArray;
        GLfloat * m_pSizeUniformArray;

        GLfloat * m_pRandomArrayCoords;
        GLfloat * m_pRandomArrayRadius;
        GLfloat * m_pRandomArraySpeed;
        GLfloat * m_pRandomArrayDelta;

        GLuint m_nCount;
        bool m_bIsVisible;

        float m_nTotalDeltaSpeed;
        float m_nDeltaSpeed;


    public:

        Particles(GLuint count,
                  GLuint programId,
                  GLuint textureId,
                  GLuint randomPositionAttr,
                  GLuint randomSpeedAttr,
                  GLuint randomRadiusAttr,
                  GLuint deltaAttr,
                  GLuint colorStartAttr,
                  GLuint colorEndAttr,
                  GLuint sizeUniform,
                  GLuint totalDeltaSpeedUniform);

        virtual ~Particles();


    public:

        void initArrays();

        void setSettings();

        void render();

        void deleteObjects();

        void setParticlesSize(GLfloat size);

        void setParticlesCount(GLuint count);

        void setVisible(bool isVisible) {
            m_bIsVisible = isVisible;
        }

        bool getVisible() {
            return m_bIsVisible;
        }


    private:

        void setValues();

};


#endif
