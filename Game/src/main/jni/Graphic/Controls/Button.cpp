#include "Button.h"

void Button::action( float _x, float _y){
	//LOGI("Button coordinates: %f - %f; %f - %f", x, y, _x, _y);
	if(_x > x && _y < y && _x < (x + width) && _y > (y - height)){
		//LOGI("Button click!");
		setTextureCoords(pressed = pressed? false : true);
	} else if(pressed){
				// If buttons lost focus
				setTextureCoords(pressed = false);
			}
}

void Button::setTextureCoords(bool isPressed){
	if(isUpButton){
		if(isPressed){
			Matrix::setTextureCoords(getTextureCoordinates(), 2, 2, Matrix::TWO);
		} else {
			Matrix::setTextureCoords(getTextureCoordinates(), 2, 2, Matrix::ONE);
		}
	} else {
		if(isPressed){
			Matrix::setTextureCoords(getTextureCoordinates(), 2, 2, Matrix::FOUR);
		} else {
			Matrix::setTextureCoords(getTextureCoordinates(), 2, 2, Matrix::THREE);
		}
	}
}

GLfloat * Button::getVerticesCoords(float x, float y, float width, float height, GLfloat * verticesCoords){

	// Top left
	verticesCoords[0] = x;
	verticesCoords[1] = y;

	// Bottom left
	verticesCoords[2] = x;
	verticesCoords[3] = y - height;

	// Bottom right
	verticesCoords[4] = x + width;
	verticesCoords[5] = y - height;

	// Top right
	verticesCoords[6] = x + width;
	verticesCoords[7] = y;

	return verticesCoords;
}