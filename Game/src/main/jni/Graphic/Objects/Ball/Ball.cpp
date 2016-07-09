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
        increaseSpeed();
        float width = getWidth();
        float centerX = Line<GLfloat>::getCenter(crossPoint->at(0), crossPoint->at(2));
        float centerY = Methods::getMax(crossPoint->at(1), crossPoint->at(3));
        float shiftY = -1.0f * Intersect::getEps();

        if(getRectangle()->getCenter().y > 0){
            width = -1.0f * width;
            sign = -1.0f;
            centerY = Methods::getMin(crossPoint->at(1), crossPoint->at(3));
            shiftY += fabsf(*getRectangle()->up.y1) - fabsf(centerY);
        } else {
                shiftY += fabsf(*getRectangle()->down.y1) - fabsf(centerY);
                sign = 1.0f;
            }

        switch(object->getRebound(centerX, centerY, width)){
            case Platform::LAST_LEFT :
                dY = -1.0f * dY;
                dX = -1.0f * sign * DX_MAX;
                moveY(sign * shiftY);
                LOGI("LAST_LEFT");
                break;
            case Platform::LEFT :
                dY = -1.0f * dY;
                dX = -1.0f * sign * DX_MIN;
                moveY(sign * shiftY);
                LOGI("LEFT");
                break;
            case Platform::CENTER :
                dY = -1.0f * dY;
                dX = 0.0f;
                moveY(sign * shiftY);
                LOGI("CENTER");
                break;
            case Platform::RIGHT :
                dY = -1.0f * dY;
                dX = sign * DX_MIN;
                moveY(sign * shiftY);
                LOGI("RIGHT");
                break;
            case Platform::LAST_RIGHT :
                dY = -1.0f * dY;
                dX = sign * DX_MAX;
                moveY(sign * shiftY);
                LOGI("LAST_RIGHT");
                break;
            case Platform::NONE :
                break;
        }

        splash->setSplashPosition(centerX, centerY);
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
                dX = -1.0f * dX;
                move();
                return true;
            }

    crossPoint->clear();

    // Right wall and up/down ball side
    if(Intersect::intersectSegments(&(object->getRectangle()->right), &(getRectangle()->up), crossPoint))
        if(Intersect::intersectSegments(&(object->getRectangle()->right), &(getRectangle()->down), crossPoint))
            if(crossPoint->size() >= 4){
                dX = -1.0f * dX;
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

    if( !Intersect::between(-1.0f, 1.0f, getRectangle()->getCenter().x) &&
        !Intersect::between(-1.0f, 1.0f, getRectangle()->getCenter().y)){
            setDefaultPosition();
            dX = 0.0f;
            isOut = true;
            return true;
    }

    return false;
}

void Ball::increaseSpeed(){
    if(fabsf(dY) < INCREASE_SPEED_TO){
        if(dY > 0)
            dY += DELTA_SPEED;
        else
            dY -= DELTA_SPEED;
    }
}
