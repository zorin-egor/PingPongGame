#include "Label.h"

Label::Label(Matrix * matrix,
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
             bool isInverse) : m_pMatrix(matrix),
                               m_fX(x),
                               m_fY(y),
                               m_fWidth(width),
                               m_fHeight(height),
                               m_nTextureId(textureID),
                               m_nProgramId(programID),
                               m_nPositionAttr(positionAttr),
                               m_nTextureAttr(textureAttr),
                               m_nTransformationAttr(transformationAttr),
                               m_sNumber(number),
                               m_bIsInverse(isInverse)
{
    LOGI("Label::Label()");
    init();
}

Label::~Label() {
    LOGI("Label::~Label()");
    clearLabels();
};

void  Label::init() {
    if (m_sNumber.length() > 0) {
        m_WidthOne = m_fWidth / (float)m_sNumber.length();

        for (int i = 0; i < m_sNumber.length(); i++) {
            char symbol = m_sNumber[i];
            int position = Methods::charToInt(symbol);

            GLfloat * textureCoord = Matrix::setTextureCoords(m_pMatrix->getDefaultTextureCoord(), 4, 4, position);
            if (m_bIsInverse) {
                Matrix::rotateTextureCoord(textureCoord, 2);
            }

            View * partOfLabel = new View(m_nTextureId,
                                          m_nProgramId,
                                          m_nPositionAttr,
                                          m_nTextureAttr,
                                          m_nTransformationAttr,
                                          Matrix::setVerticesCoords(m_fX + m_WidthOne * (float)i, m_fY, m_WidthOne, m_fHeight, m_pMatrix->getDefaultVerticesCoords()),
                                          textureCoord,
                                          m_pMatrix->getDefaultMatrix4x4());

            m_oLabelLinks.push_back(partOfLabel);
        }
    }
}

void Label::setNumber(std::string number) {
    m_sNumber = number;

    if (m_bIsInverse) {
        std::reverse(m_sNumber.begin(), m_sNumber.end());
    }

    for (int i = 0; i < m_oLabelLinks.size(); i++) {
        char symbol = m_sNumber[i];
        int position = Methods::charToInt(symbol);
        Matrix::setTextureCoords(m_oLabelLinks.at(i)->getTextureCoordinates(), 4, 4, position);

        if (m_bIsInverse) {
            Matrix::rotateTextureCoord(m_oLabelLinks.at(i)->getTextureCoordinates(), 2);
        }
    }
}

void Label::render() {
    for (auto & m_oLabelLink : m_oLabelLinks) {
        m_oLabelLink->render();
    }
}

void Label::clearLabels() {
    for (auto & m_oLabelLink : m_oLabelLinks) {
        delete m_oLabelLink;
    }

    m_oLabelLinks.clear();
}