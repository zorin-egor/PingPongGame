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
        inline static bool betweenLine(Line<A> * line, A x, A y) {
            return between(*(line->x1), *(line->x2), x) && between (*(line->y1), *(line->y2), y);
        }

        template <class A>
        static bool intersectSegments(Line<A> * line1, Line<A> * line2, std::vector<A> * twoPoints) {
            CommonLine<A> coeff1 = Intersect::coefficients(*(line1->x1), *(line1->y1), *(line1->x2), *(line1->y2));
            CommonLine<A> coeff2 = Intersect::coefficients(*(line2->x1), *(line2->y1), *(line2->x2), *(line2->y2));

            A D0 = determinate (coeff1.a, coeff1.b, coeff2.a, coeff2.b);
            A Dx = determinate (coeff1.b, coeff1.c, coeff2.b, coeff2.c);
            A Dy = -determinate (coeff1.a, coeff1.c, coeff2.a, coeff2.c);

            if (fabs(D0) < Intersect::getEps())
                return false;

            A pX = Dx / D0;
            A pY = Dy / D0;

            if(betweenLine(line1, pX, pY) && betweenLine(line2, pX, pY)){
                twoPoints->push_back(pX);
                twoPoints->push_back(pY);
                return true;
            }

            return false;
        }

        template <class A>
        static bool intersectLines(Line<A> * line1, Line<A> * line2, std::vector<A> * twoPoints) {
            CommonLine<A> coeff1 = Intersect::coefficients(*(line1->x1), *(line1->y1), *(line1->x2), *(line1->y2));
            CommonLine<A> coeff2 = Intersect::coefficients(*(line2->x1), *(line2->y1), *(line2->x2), *(line2->y2));

            A D0 = determinate (coeff1.a, coeff1.b, coeff2.a, coeff2.b);
            A Dx = determinate (coeff1.b, coeff1.c, coeff2.b, coeff2.c);
            A Dy = -determinate (coeff1.a, coeff1.c, coeff2.a, coeff2.c);

            if (fabs(D0) < Intersect::getEps())
                return false;

            twoPoints->push_back(Dx / D0);
            twoPoints->push_back(Dy / D0);

            return true;
        }

        template <class A>
        static bool intersectRect(Rectangle<A> * rect1, Rectangle<A> * rect2, std::vector<A> * crossPoints){
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++){
                    if(crossPoints->size() < 4){
                        intersectSegments(rect1->iterateLine.at(i), rect2->iterateLine.at(j), crossPoints);
                    } else
                        return true;
            }

            return false;
        }
};

#endif //GAME_PINGPONG_LINEINTERSECT_H
