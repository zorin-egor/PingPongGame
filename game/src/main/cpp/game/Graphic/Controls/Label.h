#ifndef LABEL_H
#define LABEL_H

#include "AbstractClasses/Render.h"
#include "Common/Methods.h"
#include "Common/Structures.h"
#include "Graphic/View.h"

#include <string>
#include <vector>
#include <algorithm>

class Label {

    private:

        Matrix * m_pMatrix;

        std::vector<View*> m_oLabelLinks;
        std::string m_sNumber;

        float m_fX;
        float m_fY;
        float m_fWidth;
        float m_fHeight;
        float m_WidthOne;

        GLuint m_nTextureId;
        GLuint m_nProgramId;
        GLint m_nPositionAttr;
        GLint m_nTextureAttr;
        GLint m_nTransformationAttr;

        bool m_bIsInverse;


    public:

        Label(Matrix * matrix,
              float x,
              float y,
              float width,
              float height,
              GLuint textureID,
              GLuint programID,
              GLint positionAttr,
              GLint textureAttr,
              GLint transformationAttr,
              std::string number,
              bool isInverse);

        ~Label();


    public:

        void setNumber(std::string number);

        void render();

        void clearLabels();


    private:

        void init();

};

#endif
