#include "Ball.h"

bool Ball::collision(Object * object){

    GLfloat * platformCoords = object->getPolygonCoordinates();
    GLfloat * ballCoords = getPolygonCoordinates();

    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();
    bool ya = Line::intersectRect(platformCoords, ballCoords, crossPoint);

    if(crossPoint->size() >= 4){
        setDy(-1 * getDy());
        crossPoint->clear();
        return true;
    }

    crossPoint->clear();
    return false;
}

bool Ball::collision(Platform * object){

    GLfloat * platformCoords = object->getPolygonCoordinates();
    GLfloat * ballCoords = getPolygonCoordinates();

    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();
    bool ya = Line::intersectRect(platformCoords, ballCoords, crossPoint);

    if(crossPoint->size() >= 4){
        setDy(-1 * getDy());
        crossPoint->clear();
        return true;
    }

    crossPoint->clear();
    return false;
}