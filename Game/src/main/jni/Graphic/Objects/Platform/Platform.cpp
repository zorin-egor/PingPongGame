#include "Platform.h"

bool Platform::collision(Object * object){

    move();

    // Cross points
    std::vector<GLfloat> * crossPoint = getCrossPoints();

    // Left wall
    Intersect::intersectSegments(&object->rectangle.left, &rectangle.down, crossPoint);

    // Right wall
    Intersect::intersectSegments(&object->rectangle.right, &rectangle.down, crossPoint);

    if(crossPoint->size() >= 4){
        setDx(-1.0f * getDx());
        move();
        return true;
    }

    crossPoint->clear();

    // Left wall
    Intersect::intersectSegments(&object->rectangle.left, &rectangle.up, crossPoint);

    // Left wall
    Intersect::intersectSegments(&object->rectangle.right, &rectangle.up, crossPoint);

    if(crossPoint->size() >= 4){
        setDx(-1.0f * getDx());
        move();
        return true;
    }

    crossPoint->clear();
    return false;
}

Platform::REBOUND_AREA Platform::getRebound(float x, float y, float width){
    GLfloat platformLine[4];
    GLfloat * rect = getPolygonCoordinates();

    // Find line of rectangle across with point
    for(int i = 0; i < 4; i++) {
        platformLine[0] = rect[i * 2];
        platformLine[1] = rect[i * 2 + 1];

        if (i != 3) {
            platformLine[2] = rect[i * 2 + 2];
            platformLine[3] = rect[i * 2 + 3];
        } else {
                platformLine[2] = rect[0];
                platformLine[3] = rect[1];
            }

        // If point belongs line
        if(Intersect::betweenLine(platformLine, x, y)){
            int index = 2;

            if(Intersect::between(platformLine[index], platformLine[index] + width, x))
                return Platform::LAST_LEFT;

            if(Intersect::between(platformLine[index] + width, platformLine[index] + 2.0f * width, x))
                return Platform::LEFT;

            if(Intersect::between(platformLine[index] + 2.0f * width, platformLine[index] + 3.0f * width, x))
                return Platform::CENTER;

            if(Intersect::between(platformLine[index] + 3.0f * width, platformLine[index] + 4.0f * width, x))
                return Platform::RIGHT;

            if(Intersect::between(platformLine[index] + 4.0f * width, platformLine[0], x))
                return Platform::LAST_RIGHT;
        }
    }

    return Platform::NONE;
}