#include "Ball.h"

bool Ball::collision(Platform * object){
    GLfloat * platformCoords = object->getPolygonCoordinates();
    GLfloat * ballCoords = getPolygonCoordinates();

    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    while(lastPoint.size() > 4)
        lastPoint.pop();

    // Save current points of center
    lastPoint.push(ballCoords[0] + getWidth() * 0.5f);
    lastPoint.push(ballCoords[1] - getHeight() * 0.5f);

    // It's intersect
    if(Intersect::intersectRect(platformCoords, ballCoords, crossPoint)){
        float width = getWidth();
        float sign = 1.0f;

        if(crossPoint->at(1) > 0){
            width = -1.0f * width;
            sign *= -1.0f;
        }

        float centerX = crossPoint->at(0) + (width * 0.5f);
        float centerY = crossPoint->at(1);

        switch(object->getRebound(centerX, centerY, width)){
            case Platform::LAST_LEFT :
                setDy(-1.0f * getDy());
                setDx(getDx() - sign * DX_MAX);
                break;
            case Platform::LEFT :
                setDy(-1.0f * getDy());
                setDx(getDx() - sign * DX_MIN);
                break;
            case Platform::CENTER :
                setDy(-1.0f * getDy());
                break;
            case Platform::RIGHT :
                setDy(-1.0f * getDy());
                setDx(getDx() + sign * DX_MIN);
                break;
            case Platform::LAST_RIGHT :
                setDy(-1.0f * getDy());
                setDx(getDx() + sign * DX_MAX);
                break;
            case Platform::NONE :
                break;
        }

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
    Intersect::intersectSegments(wallLine, platformLine, crossPoint);

    // Platform line up
    platformLine[0] = platformCoords[0];
    platformLine[1] = platformCoords[1];
    platformLine[2] = platformCoords[6];
    platformLine[3] = platformCoords[7];

    // Left wall
    Intersect::intersectSegments(wallLine, platformLine, crossPoint);

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
    Intersect::intersectSegments(wallLine, platformLine, crossPoint);

    // Platform line up
    platformLine[0] = platformCoords[0];
    platformLine[1] = platformCoords[1];
    platformLine[2] = platformCoords[6];
    platformLine[3] = platformCoords[7];

    // Left wall
    Intersect::intersectSegments(wallLine, platformLine, crossPoint);

    // It's intersect
    if(crossPoint->size() >= 4){
        setDx(-1.0f * getDx());
        move();
        return true;
    }

    crossPoint->clear();
    return false;
}


bool Ball::collisionUpDownWall(Object * object){
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
    Intersect::intersectSegments(wallLine, ballLine, crossPoint);

    // Ball line right
    ballLine[0] = ballCoords[4];
    ballLine[1] = ballCoords[5];
    ballLine[2] = ballCoords[6];
    ballLine[3] = ballCoords[7];

    // Left wall
    Intersect::intersectSegments(wallLine, ballLine, crossPoint);

    // It's intersect
    if(crossPoint->size() >= 4){
        setDefaultPosition();
        isOut = true;
        return true;
    }

    crossPoint->clear();

    // Up wall line
    wallLine[0] = wallCoords[6];
    wallLine[1] = wallCoords[7];
    wallLine[2] = wallCoords[0];
    wallLine[3] = wallCoords[1];

    // Platform line down
    ballLine[0] = ballCoords[0];
    ballLine[1] = ballCoords[1];
    ballLine[2] = ballCoords[2];
    ballLine[3] = ballCoords[3];

    // Left wall
    Intersect::intersectSegments(wallLine, ballLine, crossPoint);

    // Platform line up
    ballLine[0] = ballCoords[4];
    ballLine[1] = ballCoords[5];
    ballLine[2] = ballCoords[6];
    ballLine[3] = ballCoords[7];

    // Left wall
    Intersect::intersectSegments(wallLine, ballLine, crossPoint);

    // It's intersect
    if(crossPoint->size() >= 4){
        setDefaultPosition();
        isOut = true;
        return true;
    }

    crossPoint->clear();
    return false;
}
