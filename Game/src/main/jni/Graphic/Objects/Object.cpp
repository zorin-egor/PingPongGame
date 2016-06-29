#include <Common/Methods.h>
#include "Object.h"

bool Object::isObjectsInteract(Object * A, Object * B){
    GLfloat * coordsA = A->getPolygonCoordinates();
    GLfloat * coordsB = B->getPolygonCoordinates();

}

float Object::getMinimalCoords(GLfloat * a, GLfloat * b){
    float y1 = Methods::getMin(a[1], b[1]);
    float y2 = Methods::getMin(a[1], b[3]);
    float y3 =
}