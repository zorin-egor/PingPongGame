#include "Object.h"

void Object::move(){
    for(int i = 0; i < 4; i++){
        polygonCoordinates[i * 2] = polygonCoordinates[i * 2] + getDx();
        polygonCoordinates[i * 2 + 1] = polygonCoordinates[i * 2 + 1] + getDy();
    }
}

void Object::setDefaultPosition(){
    for(int i = 0; i < 8; i++){
        polygonCoordinates[i] = defaultCoords[i];
    }
}