#include "Enemy.h"

void Enemy::collision(Ball * object){
    GLfloat * rectBall = object->getPolygonCoordinates();
    GLfloat * rectEnemy = getPolygonCoordinates();

    GLfloat ballY = rectBall[1] - object->getHeight() * 0.5f;

    if(ballY > -0.2f){
        if(object->getLastPoint()->size() > 2){
            std::vector<GLfloat> crossPoint;

            // Get trajectory of ball
            GLfloat lineBall[4];
            lineBall[0] = rectBall[0] + object->getWidth() * 0.5f;
            lineBall[1] = ballY;
            lineBall[2] = object->getLastPoint()->front();
            lineBall[3] = object->getLastPoint()->front();

            // Get trajectory of enemy
            GLfloat lineEnemy[4];
            lineEnemy[0] = rectEnemy[2];
            lineEnemy[1] = rectEnemy[3];
            lineEnemy[2] = rectEnemy[4];
            lineEnemy[3] = rectEnemy[5];


            if(Line::intersectLines(lineBall, lineEnemy, &crossPoint)){
                GLfloat crossX = crossPoint.at(0);
                GLfloat centerEnemy = lineEnemy[0] + object->getWidth() * 0.5f;
                GLfloat deltaCross = getWidth() * 0.2;

                if(centerEnemy - deltaCross < crossX && crossX < centerEnemy + deltaCross){
                    dX = 0.0f;
                } else if(crossX < centerEnemy - deltaCross){
                    dX = -1.0f * getStep();
                } else if(crossX > centerEnemy + deltaCross){
                    dX = getStep();
                }
            }
        }

    } else {
            GLfloat enemyCenterX = rectEnemy[2] + getWidth() * 0.5f;
            if(enemyCenterX > 0.2f)
                dX = -1.0f * getStep();
            else if(enemyCenterX < -0.2f)
                    dX = getStep();
                 else
                    dX = 0.0f;
        }

    move();
}

void Enemy::move() {
    GLfloat * rectEnemy = getPolygonCoordinates();
    rectEnemy[0] = rectEnemy[0] + dX;
    rectEnemy[2] = rectEnemy[2] + dX;
    rectEnemy[4] = rectEnemy[4] + dX;
    rectEnemy[6] = rectEnemy[6] + dX;
};