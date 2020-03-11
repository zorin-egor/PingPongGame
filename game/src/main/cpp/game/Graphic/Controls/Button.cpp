#include "Button.h"

Button::Button(bool isSwitch,
			   bool isUpButton,
			   bool isTextureInverse,
			   float x,
			   float y,
			   float width,
			   float height,
			   int textureX,
			   int textureY,
			   Matrix::TEXTURE_COORDS positionOn,
			   Matrix::TEXTURE_COORDS positionOff,
			   GLuint textureID,
			   GLuint programID,
			   GLint positionAttr,
			   GLint textureAttr,
			   GLint transformationAttr,
			   GLfloat * verticesCoords,
			   GLfloat * textureCoords,
			   GLfloat * matrixCoords) : View(textureID,
											  programID,
											  positionAttr,
											  textureAttr,
											  transformationAttr,
											  Matrix::setVerticesCoords(x, y, width, height, verticesCoords),
											  Matrix::setTextureCoords(textureCoords, textureX, textureY, positionOff),
											  matrixCoords),
										 m_bIsSwitch(isSwitch),
										 m_bIsUpButton(isUpButton),
										 m_fX(x),
										 m_fY(y),
										 m_nWidth(width),
										 m_nHeight(height),
										 m_nTextureX(textureX),
										 m_nTextureY(textureY),
										 m_nPositionOn(positionOn),
										 m_nPositionOff(positionOff),
										 m_bIsTextureInverse(isTextureInverse)
{
	LOGI("Button::Button()");
	m_bIsPressed = false;
	m_nButtonId = -1;
	setState(m_bIsPressed);
}

Button::~Button() {
	LOGI("Button::~Button()");
}

bool Button::action(float x, float y, int buttonsId, bool isDown) {
    if (!m_bIsVisible) {
		return false;
	}

	//LOGI("Button coordinates: %f - %f; %f - %f", m_fX, m_fY, _x, m_fY);
	if (x > m_fX && y < m_fY && x < (m_fX + m_nWidth) && y > (m_fY - m_nHeight) && isDown) {
		//LOGI("Button click!");
		m_nButtonId = buttonsId;
		m_bIsBtnClicked = true;
		// If button is switch - set reverse state
		if (m_bIsSwitch) {
			setTextureCoords(m_bIsPressed = m_bIsPressed ? false : true);
		} else {
			setTextureCoords(m_bIsPressed = true);
		}
	} else if (m_bIsPressed && !m_bIsSwitch && m_nButtonId == buttonsId) {
		// If buttons lost focus
		setTextureCoords(m_bIsPressed = false);
		m_nButtonId = -1;
	}

	return m_bIsPressed;
}

void Button::setTextureCoords(bool isPressed) {
	// Set texture for button
	if (isPressed) {
		Matrix::setTextureCoords(getTextureCoordinates(), m_nTextureX, m_nTextureY, m_nPositionOn);
	} else {
		Matrix::setTextureCoords(getTextureCoordinates(), m_nTextureX, m_nTextureX, m_nPositionOff);
	}

	// Rotate texture for button
	if (m_bIsTextureInverse) {
		Matrix::rotateTextureCoord(getTextureCoordinates(), 2);
	}
}

bool Button::getState() {
	return m_bIsPressed;
}

void Button::setState(bool isPressed) {
	m_bIsPressed = isPressed;
	setTextureCoords(m_bIsPressed);
}

bool Button::isClicked() {
	bool copyIsBtnClicked = m_bIsBtnClicked;
	m_bIsBtnClicked = false;
	return copyIsBtnClicked;
}