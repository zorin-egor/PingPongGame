#ifndef GAME_MAKESHADERS_H
#define GAME_MAKESHADERS_H

#include <GLES2/gl2.h>
#include <string>

class MakeShaders {

    public :
        const static char * f_main_shader;
        const static char * v_main_shader;

        const static char * f_point_shader;
        const static char * v_point_shader;

        static GLuint compileShader(GLenum shaderType, const char* pSource);
        static GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
};

#endif //GAME_MAKESHADERS_H
