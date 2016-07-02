#include "Platform.h"

bool Platform::collision(Object * object){

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
        return true;
    }

    crossPoint->clear();
    return false;
}