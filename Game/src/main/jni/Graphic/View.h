#include <GLES2/gl2.h>
#include <iostream>
#include <typeinfo>

#include "AbstractClasses/Render.h"
#include "Common/LogGL.h"

#ifndef GAME_PINGPONG_VIEW_H
#define GAME_PINGPONG_VIEW_H

class View : public Render {

    public:
        View (  GLuint _textureID,
                GLuint _programID,
                GLint _positionAttr,
                GLint _textureAttr,
                GLint _transformationAttr,
                GLfloat * _polygonCoordinates,
                GLfloat * _textureCoordinates,
                GLfloat * _tranformationMatrix) :
                    textureID(_textureID),
                    programID(_programID),
                    positionAttr(_positionAttr),
                    textureAttr(_textureAttr),
                    transformationAttr(_transformationAttr),
                    polygonCoordinates(_polygonCoordinates),
                    textureCoordinates(_textureCoordinates),
                    transformationMatrix(_tranformationMatrix)
        {
            isVisible = true;
        }


        void render();

        void setVisible(bool _isVisible){
            isVisible = _isVisible;
        }

        bool getVisible(){
            return isVisible;
        }

        void setPolygonCoordinates(GLfloat * _polygonCoordinates){
            polygonCoordinates = _polygonCoordinates;
        }

        void setTextureCoordinates(GLfloat * _textureCoordinates){
            textureCoordinates = _textureCoordinates;
        }

        void setTransformationMatrix(GLfloat * _tranformationMatrix){
            transformationMatrix = _tranformationMatrix;
        }

        GLfloat * getPolygonCoordinates(){
            return polygonCoordinates;
        }

        GLfloat * getTextureCoordinates(){
            return textureCoordinates;
        }

        GLfloat * getTransformationMatrix(){
            return transformationMatrix;
        }

        virtual ~View(){

        }

    protected:

        bool isVisible;

        GLuint textureID;
        GLuint programID;

        GLint positionAttr;
        GLint textureAttr;
        GLint transformationAttr;

        GLfloat * polygonCoordinates;
        GLfloat * textureCoordinates;
        GLfloat * transformationMatrix;
};

#endif //GAME_PINGPONG_VIEW_H
