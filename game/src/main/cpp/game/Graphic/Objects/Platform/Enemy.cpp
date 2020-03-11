#include "Enemy.h"

Enemy::Enemy(float step,
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
             GLfloat * matrixCoords) : Platform(step,
                                                x,
                                                y,
                                                width,
                                                height,
                                                textureID,
                                                programID,
                                                positionAttr,
                                                textureAttr,
                                                transformationAttr,
                                                verticesCoords,
                                                textureCoords,
                                                matrixCoords )
{
    LOGI("Enemy::Enemy()");
    m_fDX = 0;
    setCrossHorizon(verticesCoords);
}

Enemy::~Enemy() {
    LOGI("Enemy::~Enemy()");
    delete [] m_pCrossHorizonArray;
}

void Enemy::collision(Ball * ball) {
    if (ball->getLastPoint()->size() > 2) {
        std::vector<GLfloat> crossPoint;

        // Get trajectory of m_pBall and get Line links object
        GLfloat lineBall[4];
        lineBall[0] = ball->getRectangle()->getCenter().x;
        lineBall[1] = ball->getRectangle()->getCenter().y;
        lineBall[2] = ball->getLastPoint()->front();
        ball->getLastPoint()->pop();
        lineBall[3] = ball->getLastPoint()->front();
        ball->getLastPoint()->pop();

        Line<GLfloat> pLineBall;
        pLineBall.x1 = &lineBall[0];
        pLineBall.y1 = &lineBall[1];
        pLineBall.x2 = &lineBall[2];
        pLineBall.y2 = &lineBall[3];

        // If m_pBall fly to out, else go to center!
        if (Intersect::intersectSegmentsAndLines(&m_oCrossHorizonLine, &pLineBall, &crossPoint)) {
            GLfloat crossX = crossPoint.at(0);
            GLfloat centerEnemy = getRectangle()->down.getCenterX();
            GLfloat deltaCross = getWidth() * 0.2f;

            if (centerEnemy - deltaCross < crossX && crossX < centerEnemy + deltaCross) {
                m_fDX = 0.0f;
            } else if (crossX < centerEnemy - deltaCross) {
                m_fDX = -1.0f * getStep();
            } else if (crossX > centerEnemy + deltaCross) {
                m_fDX = getStep();
            }
        } else {
            GLfloat cX = getRectangle()->getCenter().x;
            GLfloat cEps = getWidth() / 2.5f;

            if (cX > cEps) {
                m_fDX = -1.0f * getStep();
            } else if (cX < -1.0 * cEps) {
                m_fDX = getStep();
            } else {
                m_fDX = 0.0f;
            }
        }
    }
}

void Enemy::setCrossHorizon(GLfloat * crossHorizonArray) {
    m_pCrossHorizonArray = new GLfloat[4];
    m_pCrossHorizonArray[0] = -1.0f;
    m_pCrossHorizonArray[1] = crossHorizonArray[3];
    m_pCrossHorizonArray[2] = 1.0f;
    m_pCrossHorizonArray[3] = crossHorizonArray[5];

    m_oCrossHorizonLine.x1 = &m_pCrossHorizonArray[0];
    m_oCrossHorizonLine.y1 = &m_pCrossHorizonArray[1];
    m_oCrossHorizonLine.x2 = &m_pCrossHorizonArray[2];
    m_oCrossHorizonLine.y2 = &m_pCrossHorizonArray[3];
}