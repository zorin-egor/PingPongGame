#include "Button.h"

void Button::action( float _x, float _y, bool _isDown){
	//LOGI("Button coordinates: %f - %f; %f - %f", x, y, _x, _y);
	if(_x > x && _y < y && _x < (x + width) && _y > (y - height) && _isDown){
		//LOGI("Button click!");
		setTextureCoords(pressed = pressed? false : true);
	} else if(pressed && !isSwitch){
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