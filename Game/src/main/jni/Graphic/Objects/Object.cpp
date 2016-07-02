#include "Object.h"

void Object::move(){
    GLfloat * coords = getPolygonCoordinates();
    for(int i = 0; i < 4; i++){
        coords[i * 2] += getDx();
        coords[i * 2 + 1] += getDy();
    }
}