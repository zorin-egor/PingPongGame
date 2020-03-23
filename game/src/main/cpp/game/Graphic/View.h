#ifndef VIEW_H
#define VIEW_H

#include <GLES2/gl2.h>
#include <iostream>
#include <typeinfo>

#include "../AbstractClasses/Render.h"
#include "../Common/LogGL.h"
#include "../Common/Structures.h"

class View : public Render {

    protected:

        Rectangle<GLfloat> m_oRectangle;

        bool m_bIsVisible;

        GLuint m_nTextureId;
        GLuint m_nProgramId;

        GLint m_nPositionAttr;
        GLint m_nTextureAttr;
        GLint m_nTransformationAttr;

        GLfloat * m_pPolygonCoordinates;
        GLfloat * m_pTextureCoordinates;
        GLfloat * m_pTransformationMatrix;


    public:

        View (GLuint textureID,
              GLuint programID,
              GLint positionAttr,
              GLint textureAttr,
              GLint transformationAttr,
              GLfloat * polygonCoordinates,
              GLfloat * textureCoordinates,
              GLfloat * transformationMatrix);

        virtual ~View();


    public:

        void render();

        void setVisible(bool isVisible) {
            m_bIsVisible = isVisible;
        }

        bool getVisible() {
            return m_bIsVisible;
        }

        void setPolygonCoordinates(GLfloat * polygonCoordinates) {
            m_pPolygonCoordinates = polygonCoordinates;
        }

        void setTextureCoordinates(GLfloat * textureCoordinates) {
            m_pTextureCoordinates = textureCoordinates;
        }

        void setTransformationMatrix(GLfloat * transformationMatrix) {
            m_pTransformationMatrix = transformationMatrix;
        }

        GLfloat * getPolygonCoordinates() {
            return m_pPolygonCoordinates;
        }

        GLfloat * getTextureCoordinates() {
            return m_pTextureCoordinates;
        }

        GLfloat * getTransformationMatrix() {
            return m_pTransformationMatrix;
        }

        Rectangle<GLfloat> * getRectangle() {
            return &m_oRectangle;
        }

};

#endif
