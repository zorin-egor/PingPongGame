#ifndef GAME_PINGPONG_LINEINTERSECT_H
#define GAME_PINGPONG_LINEINTERSECT_H

#include <GLES2/gl2.h>
#include <cmath>
#include <vector>

#include "Common/Methods.h"

class Line {

    private:

        template <class A>
        struct line {
            A a, b, c;
        };

        template <class A>
        static float determinate(A a, A b, A c, A d) {
            return a * d - b * c;
        }

        template <class A>
        static line<A> coefficients(A x1, A y1, A x2, A y2){
            line<A> coeff;
            coeff.a = y1 - y2;
            coeff.b = x2 - x1;
            coeff.c = -1 * coeff.a * x1 - coeff.b * y1;
            return coeff;
        }

        template <class A>
        inline static bool between (A a, A b, A c) {
            return Methods::getMin(a,b) <= c + Line::getEps() && c <= Methods::getMax(a,b) + Line::getEps();
        }

        inline const static float getEps(){
            return 0.000001f;
        }

    public:

        static bool intersect (GLfloat * line1, GLfloat * line2, std::vector<GLfloat> * twoPoints) {
            line<float> coeff1 = Line::coefficients(line1[0], line1[1], line1[2], line1[3]);
            line<float> coeff2 = Line::coefficients(line2[0], line2[1], line2[2], line2[3]);

            float D0 = determinate (coeff1.a, coeff1.b, coeff2.a, coeff2.b);
            float Dx = determinate (coeff1.b, coeff1.c, coeff2.b, coeff2.c);
            float Dy = -determinate (coeff1.a, coeff1.c, coeff2.a, coeff2.c);

            if (fabs(D0) < Line::getEps())
                return false;

            float pX = Dx / D0;
            float pY = Dy / D0;

            if(between (line1[0], line1[2], pX) && between (line1[1], line1[3], pY)
               && between (line2[0], line2[2], pX) && between (line2[1], line2[3], pY)){
                twoPoints->push_back(pX);
                twoPoints->push_back(pY);
                return true;
            }

            return false;
        }

        static bool intersectRect(GLfloat * rect1, GLfloat * rect2, std::vector<GLfloat> * crossPoints){
            GLfloat lineRect1[4];
            GLfloat lineRect2[4];

            for(int i = 0; i < 4; i++){
                lineRect1[0] = rect1[i * 2];
                lineRect1[1] = rect1[i * 2 + 1];

                if(i != 3){
                    lineRect1[2] = rect1[i * 2 + 2];
                    lineRect1[3] = rect1[i * 2 + 3];
                } else {
                        lineRect1[2] = rect1[0];
                        lineRect1[3] = rect1[1];
                    }

                for(int j = 0; j < 4; j++){
                    lineRect2[0] = rect2[j * 2];
                    lineRect2[1] = rect2[j * 2 + 1];

                    if(j != 3){
                        lineRect2[2] = rect2[j * 2 + 2];
                        lineRect2[3] = rect2[j * 2 + 3];
                    } else {
                            lineRect2[2] = rect2[0];
                            lineRect2[3] = rect2[1];
                        }

                    if(crossPoints->size() < 4){
                        intersect(lineRect1, lineRect2, crossPoints);
                    } else
                        return true;
                }
            }

            return false;
        }
};

#endif //GAME_PINGPONG_LINEINTERSECT_H
