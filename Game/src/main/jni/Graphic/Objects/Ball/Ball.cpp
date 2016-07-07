#include "Ball.h"

bool Ball::collision(Platform * object){
    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    while(lastPoint.size() > 2)
        lastPoint.pop();

    // Save current points of center
    lastPoint.push(getRectangle()->getCenter().x);
    lastPoint.push(getRectangle()->getCenter().y);

    // It's intersect of two objects
    if(Intersect::intersectRect(object->getRectangle(), getRectangle(), crossPoint)){
        float width = getWidth();
        float sign = 1.0f;

        if(crossPoint->at(1) > 0){
            width = -1.0f * width;
            sign *= -1.0f;
        }

        float centerX = Line<GLfloat>::getCenter(crossPoint->at(0), crossPoint->at(2));
        float centerY = crossPoint->at(1);

        switch(object->getRebound(centerX, centerY, width)){
            case Platform::LAST_LEFT :
                setDy(-1.0f * dY);
                setDx(dX - sign * DX_MAX);
                break;
            case Platform::LEFT :
                setDy(-1.0f * dY);
                setDx(dX - sign * DX_MIN);
                break;
            case Platform::CENTER :
                setDy(-1.0f * dY);
                break;
            case Platform::RIGHT :
                setDy(-1.0f * dY);
                setDx(dX + sign * DX_MIN);
                break;
            case Platform::LAST_RIGHT :
                setDy(-1.0f * dY);
                setDx(dX + sign * DX_MAX);
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

    // It's occurs more
    if(collisionLeftRightWall(object))
        return true;

    // It's less
    if(collisionUpDownWall(object))
        return true;

    return false;
}

bool Ball::collisionLeftRightWall(Object * object) {
    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    // Left wall and up/down ball side
    if(Intersect::intersectSegments(&(object->getRectangle()->left), &(getRectangle()->up), crossPoint))
        if(Intersect::intersectSegments(&(object->getRectangle()->left), &(getRectangle()->down), crossPoint))
            if(crossPoint->size() >= 4){
                setDx(-1.0f * dX);
                move();
                return true;
            }

    crossPoint->clear();

    // Right wall and up/down ball side
    if(Intersect::intersectSegments(&(object->getRectangle()->right), &(getRectangle()->up), crossPoint))
        if(Intersect::intersectSegments(&(object->getRectangle()->right), &(getRectangle()->down), crossPoint))
            if(crossPoint->size() >= 4){
                setDx(-1.0f * dX);
                move();
                return true;
            }

    crossPoint->clear();
    return false;
}

bool Ball::collisionUpDownWall(Object * object){

    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    // Up wall and left/right ball side
    if(Intersect::intersectSegments(&object->getRectangle()->up, &getRectangle()->left, crossPoint))
        if(Intersect::intersectSegments(&object->getRectangle()->up, &getRectangle()->right, crossPoint))
            if(crossPoint->size() >= 4){
                setDefaultPosition();
                dX = 0.0f;
                isOut = true;
                return true;
            }

    crossPoint->clear();

    // Down wall and left/right ball side
    if(Intersect::intersectSegments(&object->getRectangle()->down, &getRectangle()->left, crossPoint))
        if(Intersect::intersectSegments(&object->getRectangle()->down, &getRectangle()->right, crossPoint))
            if(crossPoint->size() >= 4){
                setDefaultPosition();
                dX = 0.0f;
                isOut = true;
                return true;
            }

    crossPoint->clear();
    return false;
}
