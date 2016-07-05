#ifndef GAME_PINGPONG_LINEINTERSECT_H
#define GAME_PINGPONG_LINEINTERSECT_H

#include <GLES2/gl2.h>
#include <cmath>
#include <vector>

#include "Common/Methods.h"
#include "Common/Structures.h"

class Intersect {

    private:

        inline static const float getEps(){
            return 0.000001f;
        }

        template <class A>
        static float determinate(A a, A b, A c, A d) {
            return a * d - b * c;
        }

        template <class A>
        static CommonLine<A> coefficients(A x1, A y1, A x2, A y2){
            CommonLine<A> coeff;
            coeff.a = y1 - y2;
            coeff.b = x2 - x1;
            coeff.c = -1 * coeff.a * x1 - coeff.b * y1;
            return coeff;
        }

    public:

        template <class A>
        inline static bool between (A a, A b, A c) {
            return Methods::getMin(a,b) <= c + Intersect::getEps() && c <= Methods::getMax(a, b) + Intersect::getEps();
        }

        template <class A>
        inline static bool betweenLine(A * line, A x, A y) {
            return between(line[0], line[2], x) && between (line[1], line[3], y);
        }

        static bool intersectSegments(Line<GLfloat> * line1, Line<GLfloat> * line2, std::vector<GLfloat> *twoPoints) {
            CommonLine<GLfloat *> coeff1 = Intersect::coefficients(line1->x1, line1->y1, line1->x2, line1->y2);
            CommonLine<GLfloat *> coeff2 = Intersect::coefficients(line2->x1, line2->y1, line2->x2, line2->y2);

            float D0 = determinate (coeff1.a, coeff1.b, coeff2.a, coeff2.b);
            float Dx = determinate (coeff1.b, coeff1.c, coeff2.b, coeff2.c);
            float Dy = -determinate (coeff1.a, coeff1.c, coeff2.a, coeff2.c);

            if (fabs(D0) < Intersect::getEps())
                return false;

            float pX = Dx / D0;
            float pY = Dy / D0;

            if(betweenLine(line1, pX, pY) && betweenLine(line2, pX, pY)){
                twoPoints->push_back(pX);
                twoPoints->push_back(pY);
                return true;
            }

            return false;
        }

        static bool intersectLines(Line<GLfloat> * line1, Line<GLfloat> * line2, std::vector<GLfloat> * twoPoints) {
            CommonLine<GLfloat *> coeff1 = Intersect::coefficients(line1->x1, line1->y1, line1->x2, line1->y2);
            CommonLine<GLfloat *> coeff2 = Intersect::coefficients(line2->x1, line2->y1, line2->x2, line2->y2);

            float D0 = determinate (coeff1.a, coeff1.b, coeff2.a, coeff2.b);
            float Dx = determinate (coeff1.b, coeff1.c, coeff2.b, coeff2.c);
            float Dy = -determinate (coeff1.a, coeff1.c, coeff2.a, coeff2.c);

            if (fabs(D0) < Intersect::getEps())
                return false;

            twoPoints->push_back(Dx / D0);
            twoPoints->push_back(Dy / D0);

            return true;
        }


        static bool intersectRect(GLfloat * rect1, GLfloat * rect2, std::vector<GLfloat> * crossPoints){
            Line<GLfloat> lineRect1;
            Line<GLfloat> lineRect2;

            for(int i = 0; i < 4; i++){
                lineRect1.x1 = &rect1[i * 2];
                lineRect1.y1 = &rect1[i * 2 + 1];

                if(i != 3){
                    lineRect1.x2 = &rect1[i * 2 + 2];
                    lineRect1.y2 = &rect1[i * 2 + 3];
                } else {
                        lineRect1.x2 = &rect1[0];
                        lineRect1.y2 = &rect1[1];
                    }

                for(int j = 0; j < 4; j++){
                    lineRect2.x1 = &rect2[j * 2];
                    lineRect2.y1 = &rect2[j * 2 + 1];

                    if(j != 3){
                        lineRect2.x2 = &rect2[j * 2 + 2];
                        lineRect2.y2 = &rect2[j * 2 + 3];
                    } else {
                            lineRect2.x2 = &rect2[0];
                            lineRect2.y2 = &rect2[1];
                        }

                    if(crossPoints->size() < 4){
                        intersectSegments(&lineRect1, &lineRect2, crossPoints);
                    } else
                        return true;
                }
            }

            return false;
        }
};

#endif //GAME_PINGPONG_LINEINTERSECT_H
