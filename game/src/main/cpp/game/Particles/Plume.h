#ifndef PLUME_H
#define PLUME_H

#include <queue>
#include "Splash.h"

class Plume : public Render {

    private:

        const GLuint MAX_COUNT;
        const GLuint MAX_SIZE;
        const GLuint MIN_SIZE;

        bool m_bIsVisible;

        GLuint m_nCount;
        GLuint m_nProgramID;
        GLuint m_nTextureID;
        GLuint m_nPositionAttr;
        GLuint m_nColorStartAttr;
        GLuint m_nColorEndAttr;
        GLuint m_nDeltaAttr;
        GLuint m_nSizeUniform;
        GLfloat m_fPointSize;

        GLfloat * m_pPositionArray;
        GLfloat * m_pColorStartArray;
        GLfloat * m_pColorEndArray;
        GLfloat * m_pDeltaArray;
        GLfloat * m_pSizeArray;


    public:

        Plume(GLuint count,
              GLuint programID,
              GLuint textureID,
              GLuint positionAttr,
              GLuint colorStartAttr,
              GLuint colorEndAttr,
              GLuint deltaAttr,
              GLuint sizeUniform);

        virtual ~Plume();


    public:

        void initArrays();

        void setSettings();

        void render();

        void setParticlesCount(GLuint count);

        void setParticlesSize(GLfloat size);

        void setPlumePoints(std::queue<GLfloat> * points);

        void deleteObjects();

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
