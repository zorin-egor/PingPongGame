#ifndef GAME_PINGPONG_STRUCTURES_H
#define GAME_PINGPONG_STRUCTURES_H

#include <GLES2/gl2.h>
#include <vector>
#include <cmath>

class Matrix {

private:
    std::vector<GLfloat *> arrayLInks;

public:

    static const enum TEXTURE_COORDS {  ONE = 0, TWO = 1, THREE = 2, FOUR = 3,
                                        FIFE = 4, SIX = 5, SEVEN = 6, EIGHT  = 7,
                                        NINE = 8, TEN = 8, ELEVEN = 10, TWELVE = 11,
                                        THIRTEEN  = 12, FOURTEEN = 13, FIFTEEN = 14, SIXTEEN = 15 };

    static const enum COORDINATES { X = 1, Y = 2, Z = 3};

    ~Matrix(){
        // Clear all link on arrays
        if(!arrayLInks.empty())
            for (std::vector<GLfloat *>::iterator it = arrayLInks.begin(); it != arrayLInks.end(); it++)
                delete [] *it;
    }

    GLfloat * getDefaultMatrix4x4(){
        GLfloat * matrix = new GLfloat[16];
        arrayLInks.push_back(matrix);

        // 1 строка
        matrix[0] = 1.0f;
        matrix[1] = 0.0f;
        matrix[2] = 0.0f;
        matrix[3] = 0.0f;

        // 2 строка
        matrix[4] = 0.0f;
        matrix[5] = 1.0f;
        matrix[6] = 0.0f;
        matrix[7] = 0.0f;

        // 3 строка
        matrix[8] = 0.0f;
        matrix[9] = 0.0f;
        matrix[10] = 1.0f;
        matrix[11] = 0.0f;

        // 4 строка
        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = 0.0f;
        matrix[15] = 1.0f;

        return matrix;
    }

    GLfloat * getDefaultTextureCoord(){
        // 1---4
        // |   |
        // 2---3

        GLfloat * texture = new GLfloat[8];
        arrayLInks.push_back(texture);

        // 1 вершина
        texture[0] = 0.0f;
        texture[1] = 0.0f;

        // 2 вершина
        texture[2] = 0.0f;
        texture[3] = 1.0f;

        // 3 вершина
        texture[4] = 1.0f;
        texture[5] = 1.0f;

        // 4 вершина
        texture[6] = 1.0f;
        texture[7] = 0.0f;

        return texture;
    }

    GLfloat * getDefaultVerticesCoords(){
        // 1---4
        // | \ |
        // 2---3

        GLfloat * vertices = new GLfloat[8];
        arrayLInks.push_back(vertices);

        // 1 вершина
        vertices[0] = -1.0f;
        vertices[1] = 1.0f;

        // 2 вершина
        vertices[2] = -1.0f;
        vertices[3] = -1.0f;

        // 3 вершина
        vertices[4] = 1.0f;
        vertices[5] = -1.0f;

        // 4 вершина
        vertices[6] = 1.0f;
        vertices[7] = 1.0f;

        return vertices;
    }

    static GLfloat * setTextureCoords(GLfloat * textureCoords, int x, int y, int number){
        int cells = x * y;

        if(0 <= number && number < cells && x > 0 && y > 0){
            float x_cell = 1.0f / (float) x;
            float y_cell = 1.0f / (float) y;

            float position = (float)number * x_cell;
            float new_y;
            float new_x = std::modf(position, &new_y);

            new_y *= y_cell;

            // 1 вершина
            textureCoords[0] = new_x;
            textureCoords[1] = new_y;

            // 2 вершина
            textureCoords[2] = new_x;
            textureCoords[3] = new_y + y_cell;

            // 3 вершина
            textureCoords[4] = new_x + x_cell;
            textureCoords[5] = new_y + y_cell;

            // 4 вершина
            textureCoords[6] = new_x + x_cell;
            textureCoords[7] = new_y;
        }

        return textureCoords;
    }

    static GLfloat * setMoveMatrix4x4(GLfloat * textureCoords, GLfloat x, GLfloat y){
        textureCoords[12] = x;
        textureCoords[13] = y;
        textureCoords[14] = 1.0f;

        return textureCoords;
    }

    static  GLfloat * setScaleMatrix4x4(GLfloat * textureCoords, GLfloat x, GLfloat y){
        textureCoords[0] = 1.0f;
        textureCoords[5] = y;
        textureCoords[10] = x;

        return textureCoords;
    }

    static  GLfloat * setRotateMatrix4x4(GLfloat * textureCoords, GLfloat a, COORDINATES axis){
        switch(axis){
            case X :
                textureCoords[5] = cos(a);
                textureCoords[6] = sin(a);
                textureCoords[9] = -sin(a);
                textureCoords[10] = cos(a);
                break;
            case Y :
                textureCoords[0] = cos(a);
                textureCoords[2] = -sin(a);
                textureCoords[8] = sin(a);
                textureCoords[10] = cos(a);
                break;
            case Z :
                textureCoords[0] = cos(a);
                textureCoords[1] = sin(a);
                textureCoords[4] = -sin(a);
                textureCoords[6] = cos(a);
                break;
        }

        return textureCoords;
    }
};

#endif //GAME_PINGPONG_STRUCTURES_H
