#include "Button.h"

bool Button::action( float _x, float _y, int _buttonId, bool _isDown){
	//LOGI("Button coordinates: %f - %f; %f - %f", x, y, _x, _y);
	if(_x > x && _y < y && _x < (x + width) && _y > (y - height) && _isDown){
		//LOGI("Button click!");
		buttonId = _buttonId;

		// If button is switch - set reverse state
		if(isSwitch)
			setTextureCoords(pressed = pressed? false : true);
		else
			setTextureCoords(pressed = true);

	} else if(pressed && !isSwitch && buttonId == _buttonId){
				// If buttons lost focus
				setTextureCoords(pressed = false);
				buttonId = -1;
			}

	return pressed;
}

void Button::setTextureCoords(bool isPressed){
	if(isPressed){
		Matrix::setTextureCoords(getTextureCoordinates(), textureX, textureY, positionOn);
	} else {
		Matrix::setTextureCoords(getTextureCoordinates(), textureX, textureX, positionOff);
	}
}