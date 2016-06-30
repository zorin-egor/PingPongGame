#ifndef GAME_PINGPONG_METHODS_H
#define GAME_PINGPONG_METHODS_H

#include <ctime>
#include <stdlib.h>
#include <string>
#include <GLES2/gl2.h>

class Methods {

    public:

        inline static float getFullRandom(){
            return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 2) - 1;
        }

        inline static float getShortRandom(){
            return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }

        inline static float convertCoordinatesToOpenGL(bool inverse, int screenSize, float coordinate){
            return (coordinate / screenSize * 2 - 1) * (inverse? -1 : 1);
        }

        template <class A, class B>
        static void fillArray(A * array, B content, int count){
            for(int i = 0; i < count; i++)
                array[i] = (A)content;
        }

        static std::string fillLeft(std::string stringForFill, char symbole, int toLenght){
            int difference = toLenght - stringForFill.length();
            if(difference > 0){
                std::string buf(difference, symbole);
                stringForFill = buf + stringForFill;
            }

            return stringForFill;
        }

        static std::string intToStrong(int number){
            std::string result = "";
                while(number){
                    int x = number % 10;
                    number /= 10;
                    char i = '0';
                    i = i + x;
                    result = i + result;
                }

            return result;
        }

        template <class A>
        inline static A getMin(A a, A b){
            return a < b? a : b;
        }

        template <class A>
        inline static A getMax(A a, A b){
            return a > b? a : b;
        }
};

#endif //GAME_PINGPONG_METHODS_H
