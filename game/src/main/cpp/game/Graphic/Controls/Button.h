#ifndef BUTTON_H
#define BUTTON_H

#include "../../Common/Structures.h"
#include "../../Common/LogGL.h"
#include "../View.h"

class Button : public View {

	private:

		bool m_bIsBtnClicked;
		bool m_bIsSwitch;
		bool m_bIsUpButton;
		bool m_bIsTextureInverse;

		int m_nButtonId;

		float m_nWidth;
		float m_nHeight;
		float m_fX;
		float m_fY;

		// Texture grid
		int m_nTextureX;
		int m_nTextureY;
		int m_nPositionOn;
		int m_nPositionOff;

		// Button state
		bool m_bIsPressed;


	public:

		Button(bool isSwitch,
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
			   GLfloat * matrixCoords);

		virtual ~Button();


	public:

		bool action(float x, float y, int buttonsId, bool isDown);

		bool getState();

		void setState(bool isPressed);

		bool isClicked();


	private:

		void setTextureCoords(bool isPressed);
};

#endif
