#include "Enemy.h"

void Enemy::collision(Ball * object){
    if(object->getLastPoint()->size() > 2){
        std::vector<GLfloat> crossPoint;

        // Get trajectory of ball and get Line links object
        GLfloat lineBall[4];
        lineBall[0] = object->getRectangle()->getCenter().x;
        lineBall[1] = object->getRectangle()->getCenter().y;
        lineBall[2] = object->getLastPoint()->front();
        object->getLastPoint()->pop();
        lineBall[3] = object->getLastPoint()->front();
        object->getLastPoint()->pop();

        Line<GLfloat> pLineBall;
        pLineBall.x1 = &lineBall[0];
        pLineBall.y1 = &lineBall[1];
        pLineBall.x2 = &lineBall[2];
        pLineBall.y2 = &lineBall[3];

        // If ball fly to out, else go to center!
        if(Intersect::intersectSegmentsAndLines(&crossHorizonLine, &pLineBall, &crossPoint)){
            GLfloat crossX = crossPoint.at(0);
            GLfloat centerEnemy = getRectangle()->down.getCenterX();
            GLfloat deltaCross = getWidth() * 0.2f;

            if(centerEnemy - deltaCross < crossX && crossX < centerEnemy + deltaCross){
                dX = 0.0f;
            } else if(crossX < centerEnemy - deltaCross){
                dX = -1.0f * getStep();
            } else if(crossX > centerEnemy + deltaCross){
                dX = getStep();
            }
        } else {
                GLfloat cX = getRectangle()->getCenter().x;
                GLfloat cEps = getWidth() / 2.5f;
                if(cX> cEps)
                    dX = -1.0f * getStep();
                else if(cX < -1.0 * cEps)
                        dX = getStep();
                     else
                        dX = 0.0f;
            }
    }

    Platform::collision(object);
}

void Enemy::setCrossHorizont(GLfloat * _crossHorizontArray){
    crossHorizonArray = new GLfloat[4];
    crossHorizonArray[0] = -1.0f;
    crossHorizonArray[1] = _crossHorizontArray[3];
    crossHorizonArray[2] = 1.0f;
    crossHorizonArray[3] = _crossHorizontArray[5];

    crossHorizonLine.x1 = &crossHorizonArray[0];
    crossHorizonLine.y1 = &crossHorizonArray[1];
    crossHorizonLine.x2 = &crossHorizonArray[2];
    crossHorizonLine.y2 = &crossHorizonArray[3];
}