#include "Object.h"

void Object::move(){
    for(int i = 0; i < 4; i++){
        polygonCoordinates[i * 2] += dX;
        polygonCoordinates[i * 2 + 1] += dY;
    }
}

void Object::moveX(GLfloat x){
    for(int i = 0; i < 4; i++){
        polygonCoordinates[i * 2] += x;
    }
}

void Object::moveY(GLfloat y){
    for(int i = 0; i < 4; i++){
        polygonCoordinates[i * 2 + 1] += y;
    }
}

void Object::setDefaultPosition(){
    for(int i = 0; i < 8; i++){
        polygonCoordinates[i] = defaultCoords[i];
    }

    dY *= Methods::getRandSign();
    //dY *= 1.0f;
}