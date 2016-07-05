#include "Enemy.h"

void Enemy::collision(Ball * object){
    if(object->getLastPoint()->size() > 2){
        std::vector<GLfloat> crossPoint;

        // Get trajectory of ball
        GLfloat lineBall[4];
        lineBall[0] = getRectangle()->getCenter().x;
        lineBall[1] = getRectangle()->getCenter().y;
        lineBall[2] = object->getLastPoint()->front();
        lineBall[3] = object->getLastPoint()->front();

        Line<GLfloat> pLineBall;
        pLineBall.x1 = &lineBall[0];
        pLineBall.y1 = &lineBall[1];
        pLineBall.x2 = &lineBall[2];
        pLineBall.y2 = &lineBall[3];

        if(Intersect::intersectLines(&pLineBall, &getRectangle()->down, &crossPoint)){
            GLfloat crossX = crossPoint.at(0);
            GLfloat centerEnemy = getRectangle()->down.getCenterX() + object->getWidth() * 0.5f;
            GLfloat deltaCross = getWidth() * 0.2f;

            if(centerEnemy - deltaCross < crossX && crossX < centerEnemy + deltaCross){
                dX = 0.0f;
            } else if(crossX < centerEnemy - deltaCross){
                dX = -1.0f * getStep();
            } else if(crossX > centerEnemy + deltaCross){
                dX = getStep();
            }
        }
    }

    move();
}