#ifndef BUTTON_H_
#define BUTTON_H_

#include "Graphic/View.h"
#include "Common/Structures.h"
#include "Common/LogGL.h"

class Button : public View {

	public:

		Button(bool _isSwitch,
			   bool _isUpButton,
			   float _x,
			   float _y,
			   float _width,
			   float _height,
			   GLuint _textureID,
			   GLuint _programID,
			   GLint _positionAttr,
			   GLint _textureAttr,
			   GLint _transformationAttr,
			   GLfloat * _verticesCoords,
			   GLfloat * _textureCoords,
			   GLfloat * _matrixCoords) : View(	_textureID,
											 	_programID,
											 	_positionAttr,
											 	_textureAttr,
											 	_transformationAttr,
											 	Matrix::setVerticesCoords(_x, _y, _width, _height, _verticesCoords),
											    _textureCoords,
											    _matrixCoords),

										  	isSwitch(_isSwitch),
											isUpButton(_isUpButton),
											x(_x),
											y(_y),
											width(_width),
											height(_height)
		{
			pressed = false;
		}

		bool getState(){
			return pressed;
		};

		void setState(bool _pressed){
			pressed = _pressed;
			setTextureCoords(pressed);
		}

		void action(float _x, float _y);

	private:

		bool isSwitch;
		bool isUpButton;

		// Button position
		float width, height;
		float x, y;

		// Button state
		bool pressed;

		void setTextureCoords(bool isPressed);
};

#endif /* BUTTON_H_ */
