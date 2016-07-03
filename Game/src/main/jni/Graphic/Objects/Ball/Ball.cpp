#include "Ball.h"

bool Ball::collision(Platform * object){
    GLfloat * platformCoords = object->getPolygonCoordinates();
    GLfloat * ballCoords = getPolygonCoordinates();

    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();
    bool ya = Line::intersectRect(platformCoords, ballCoords, crossPoint);

    // It's intersect
    if(crossPoint->size() >= 4){
        float width = crossPoint->at(1) > 0? -1.0 * getWidth() : getWidth();
        float centerX = crossPoint->at(0) + (getWidth() * 0.5f);
        float centerY = crossPoint->at(1);

        switch(object->getRebound(centerX, centerY, width)){
            case Platform::LAST_LEFT :
                break;
            case Platform::LEFT :
                break;
            case Platform::CENTER :
                break;
            case Platform::RIGHT :
                break;
            case Platform::LAST_RIGHT :
                break;
            case Platform::NONE :
                break;
        }

        setDy(-1 * getDy());
        crossPoint->clear();
        return true;
    }

    crossPoint->clear();
    return false;
}

bool Ball::collision(Object * object){

    if(collisionLeftRightWall(object))
        return true;

    if(collisionUpDownWall(object))
        return true;

    return false;
}

bool Ball::collisionLeftRightWall(Object *object) {
    GLfloat * wallCoords = object->getPolygonCoordinates();
    GLfloat * platformCoords = getPolygonCoordinates();

    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    // Wall line
    GLfloat wallLine[4];

    // Platform line
    GLfloat platformLine[4];

    // Left wall line
    wallLine[0] = wallCoords[0];
    wallLine[1] = wallCoords[1];
    wallLine[2] = wallCoords[2];
    wallLine[3] = wallCoords[3];

    // Platform line down
    platformLine[0] = platformCoords[2];
    platformLine[1] = platformCoords[3];
    platformLine[2] = platformCoords[4];
    platformLine[3] = platformCoords[5];

    // Left wall
    Line::intersect(wallLine, platformLine, crossPoint);

    // Platform line up
    platformLine[0] = platformCoords[0];
    platformLine[1] = platformCoords[1];
    platformLine[2] = platformCoords[6];
    platformLine[3] = platformCoords[7];

    // Left wall
    Line::intersect(wallLine, platformLine, crossPoint);

    // It's intersect
    if(crossPoint->size() >= 4){
        setDx(-1.0f * getDx());
        move();
        return true;
    }

    crossPoint->clear();

    // Right wall line
    wallLine[0] = wallCoords[4];
    wallLine[1] = wallCoords[5];
    wallLine[2] = wallCoords[6];
    wallLine[3] = wallCoords[7];

    // Platform line down
    platformLine[0] = platformCoords[2];
    platformLine[1] = platformCoords[3];
    platformLine[2] = platformCoords[4];
    platformLine[3] = platformCoords[5];

    // Left wall
    Line::intersect(wallLine, platformLine, crossPoint);

    // Platform line up
    platformLine[0] = platformCoords[0];
    platformLine[1] = platformCoords[1];
    platformLine[2] = platformCoords[6];
    platformLine[3] = platformCoords[7];

    // Left wall
    Line::intersect(wallLine, platformLine, crossPoint);

    // It's intersect
    if(crossPoint->size() >= 4){
        setDx(-1.0f * getDx());
        move();
        return true;
    }

    crossPoint->clear();
    return false;
}


bool Ball::collisionUpDownWall(Object *object){
    GLfloat * wallCoords = object->getPolygonCoordinates();
    GLfloat * ballCoords = getPolygonCoordinates();

    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    // Wall line
    GLfloat wallLine[4];

    // Ball line
    GLfloat ballLine[4];

    // Down wall line
    wallLine[0] = wallCoords[2];
    wallLine[1] = wallCoords[3];
    wallLine[2] = wallCoords[4];
    wallLine[3] = wallCoords[5];

    // Ball line left
    ballLine[0] = ballCoords[0];
    ballLine[1] = ballCoords[1];
    ballLine[2] = ballCoords[2];
    ballLine[3] = ballCoords[3];

    // Left wall
    Line::intersect(wallLine, ballLine, crossPoint);

    // Ball line up
    ballLine[0] = ballCoords[4];
    ballLine[1] = ballCoords[5];
    ballLine[2] = ballCoords[6];
    ballLine[3] = ballCoords[7];

    // Left wall
    Line::intersect(wallLine, ballLine, crossPoint);

    // It's intersect
    if(crossPoint->size() >= 4){
        setDefaultPosition();
        isOut = true;
        return true;
    }

    crossPoint->clear();

    // Up wall line
    wallLine[0] = wallCoords[5];
    wallLine[1] = wallCoords[6];
    wallLine[2] = wallCoords[0];
    wallLine[3] = wallCoords[1];

    // Platform line down
    ballLine[0] = ballCoords[2];
    ballLine[1] = ballCoords[3];
    ballLine[2] = ballCoords[4];
    ballLine[3] = ballCoords[5];

    // Left wall
    Line::intersect(wallLine, ballLine, crossPoint);

    // Platform line up
    ballLine[0] = ballCoords[4];
    ballLine[1] = ballCoords[5];
    ballLine[2] = ballCoords[6];
    ballLine[3] = ballCoords[7];

    // Left wall
    Line::intersect(wallLine, ballLine, crossPoint);

    // It's intersect
    if(crossPoint->size() >= 4){
        setDefaultPosition();
        isOut = true;
        return true;
    }

    crossPoint->clear();
    return false;
}
