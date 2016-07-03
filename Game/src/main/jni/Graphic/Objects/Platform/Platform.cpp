#include "Platform.h"

bool Platform::collision(Object * object){

    move();

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
        if(Line::betweenLine(platformLine, x, y)){
            int index = 2;

            if(Line::between(platformLine[index], platformLine[index] + width, x))
                return Platform::LAST_LEFT;

            if(Line::between(platformLine[index] + width, platformLine[index] + 2.0f * width, x))
                return Platform::LEFT;

            if(Line::between(platformLine[index] + 2.0f * width, platformLine[index] + 3.0f * width, x))
                return Platform::CENTER;

            if(Line::between(platformLine[index] + 3.0f * width, platformLine[index] + 4.0f * width, x))
                return Platform::RIGHT;

            if(Line::between(platformLine[index] + 4.0f * width, platformLine[0], x))
                return Platform::LAST_RIGHT;
        }
    }

    return Platform::NONE;
}