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

        static std::string intToString(int number){
            std::string result = number == 0? "0" : "";
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
        static A * shiftArrayLeft(A * array, int size){
            A temp = array[0];
            for(int i = 1; i < size; i++)
                array[i - 1] = array[i];

            array[size - 1] = temp;
            return array;
        }

        template <class A>
        static A * shiftArrayRight(A * array, int size){
            A temp = array[size - 1];
            for(int i = size - 1; i >= 0 ; i--)
                array[i] = array[i - 1];

            array[0] = temp;
            return array;
        }

        template <class A>
        static A * mirrorArray(A * array, int size){
            A temp;
            for(int i = 0; i < size / 2; i++){
                temp = array[i];
                array[i] = array[size - 1 - i];
                array[size - 1 - i] = temp;
            }

            return array;
        }

        inline static int getRandSign(){
            int sign[2] = {-1, 1};
            return sign[rand() % 2];
        }

        template <class A>
        inline static A getMin(A a, A b){
            return a < b? a : b;
        }

        template <class A>
        inline static A getMax(A a, A b){
            return a > b? a : b;
        }

        template <class A>
        inline static void swap(A & a, A & b){
            A temp = b;
            b = a;
            a = temp;
        }
};

#endif //GAME_PINGPONG_METHODS_H
