#ifndef GAME_MAKESHADERS_H
#define GAME_MAKESHADERS_H

#include <GLES2/gl2.h>
#include <string>

class MakeShaders {

    public :
        // Shaders for draw objects
        const static char * f_main_shader;
        const static char * v_main_shader;

        // Shader for draw background points
        const static char * f_point_shader;
        const static char * v_point_shader;

        // Shader for draw splash for collision
        const static char * f_splash_shader;
        const static char * v_splash_shader;

        // Shader for draw background shape
        const static char * f_shape_shader;
        const static char * v_shape_shader;

        // For compiling shader program
        static GLuint compileShader(GLenum shaderType, const char* pSource);

        // For create shader program
        static GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
};

#endif //GAME_MAKESHADERS_H
