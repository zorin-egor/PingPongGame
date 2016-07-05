#include "Platform.h"

bool Platform::collision(Object * object){

    move();

    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    // Left side
    Intersect::intersectSegments(&object->getRectangle()->left, &getRectangle()->down, crossPoint);

    // Right side
    Intersect::intersectSegments(&object->getRectangle()->left, &getRectangle()->up, crossPoint);

    if(crossPoint->size() >= 4){
        setDx(-1.0f * dX);
        move();
        return true;
    }

    crossPoint->clear();

    // Left side
    Intersect::intersectSegments(&object->getRectangle()->right, &getRectangle()->down, crossPoint);

    // Right side
    Intersect::intersectSegments(&object->getRectangle()->right, &getRectangle()->up, crossPoint);

    if(crossPoint->size() >= 4){
        setDx(-1.0f * dX);
        move();
        return true;
    }

    crossPoint->clear();
    return false;
}

Platform::REBOUND_AREA Platform::getRebound(float x, float y, float width){
    // Find line of rectangle across with point
    for(int i = 0; i < 4; i++) {
        // If point belongs line
        if(Intersect::betweenLine(getRectangle()->iterateLine.at(i), x, y)){

            if(Intersect::between(*getRectangle()->iterateLine.at(i)->x1, *getRectangle()->iterateLine.at(i)->x1 + width, x))
                return Platform::LAST_LEFT;

            if(Intersect::between(*getRectangle()->iterateLine.at(i)->x1 + width, *getRectangle()->iterateLine.at(i)->x1 + 2.0f * width, x))
                return Platform::LEFT;

            if(Intersect::between(*getRectangle()->iterateLine.at(i)->x1 + 2.0f * width, *getRectangle()->iterateLine.at(i)->x1 + 3.0f * width, x))
                return Platform::CENTER;

            if(Intersect::between(*getRectangle()->iterateLine.at(i)->x1 + 3.0f * width, *getRectangle()->iterateLine.at(i)->x1 + 4.0f * width, x))
                return Platform::RIGHT;

            if(Intersect::between(*getRectangle()->iterateLine.at(i)->x1 + 4.0f * width, *getRectangle()->iterateLine.at(i)->x2, x))
                return Platform::LAST_RIGHT;
        }
    }

    return Platform::NONE;
}