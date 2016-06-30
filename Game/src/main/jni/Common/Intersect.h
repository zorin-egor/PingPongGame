#ifndef GAME_PINGPONG_LINEINTERSECT_H
#define GAME_PINGPONG_LINEINTERSECT_H

#include <GLES2/gl2.h>
#include <stdlib.h>

class Line {

    private:

        struct line {
            float a, b, c;
        };

        static float determinate(float a, float b, float c, float d) {
            return a * d - b * c;
        }

        static line & coefficients(float x1, float y1, float x2, float y2){
            line coeff;
            coeff.a = y1 - y2;
            coeff.b = x2 - x1;
            coeff.c = x1 * y2 - x2 * y1;
            return coeff;
        }

    public:
        static bool intersect(GLfloat * line1, GLfloat * line2, GLfloat * point) {
            line & coeff1 = Line::coefficients(line1[0], line1[1], line1[2], line1[3]);
            line & coeff2 = Line::coefficients(line2[0], line2[1], line2[2], line2[3]);

            float zn = Line::determinate(coeff1.a, coeff1.b, coeff2.a, coeff2.b);

            if (abs(zn) < 0.00000001f)
                return false;

            point[0] -= Line::determinate(coeff1.c, coeff1.b, coeff1.c, coeff1.b) / zn;
            point[1] -= Line::determinate(coeff1.a, coeff1.c, coeff1.a, coeff1.c) / zn;

            return true;
        }
};

#endif //GAME_PINGPONG_LINEINTERSECT_H
