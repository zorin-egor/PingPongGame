#ifndef SPLASH_H
#define SPLASH_H


#include <GLES2/gl2.h>
#include "../AbstractClasses/Render.h"
#include "../Common/LogGL.h"
#include "../Common/Methods.h"

class Splash : public Render {

    private:

        const GLuint TOTAL_LIFE_TIME;

        bool m_pIsVisible;

        GLuint m_nCount;
        GLint m_nLifeTime;

        GLuint m_nProgramId;
        GLuint m_nTextureId;
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

        GLfloat * m_pDxArray;
        GLfloat * m_pDyArray;


    public:

        Splash(GLuint count,
               GLuint lifeTime,
               GLuint programID,
               GLuint textureID,
               GLuint positionAttr,
               GLuint colorStartAttr,
               GLuint colorEndAttr,
               GLuint deltaAttr,
               GLuint sizeUniform );

        virtual ~Splash();


    public:

        void initArrays();

        void render();

        void setSettings();

        void deleteObjects();

        void setParticlesCount(GLuint count);

        void setParticlesSize(GLfloat size);

        void setSplashPosition(GLfloat x, GLfloat y);

        void resetTimer();

        void setVisible(bool isVisible) {
            m_pIsVisible = isVisible;
        }

        bool getVisible() {
            return m_pIsVisible;
        }


    private:

        void setValues();

};

#endif
