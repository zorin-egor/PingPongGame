#ifndef MAKE_SHADERS_H
#define MAKE_SHADERS_H

#include <GLES2/gl2.h>
#include <string>

class MakeShaders {

    public :

        // Shader for draw objects
        static const char * F_MAIN_SHADER;
        static const char * V_MAIN_SHADER;

        // Shader for draw background points
        static const char * F_POINT_SHADER;
        static const char * V_POINT_SHADER;

        // Shader for draw splash for collision
        static const char * F_SPLASH_SHADER;
        static const char * V_SPLASH_SHADER;

        // Shader for draw background shape
        static const char * F_SHAPE_SHADER;
        static const char * V_SHAPE_SHADER;

        // For compiling shader program
        static GLuint compileShader(GLenum shaderType, const char* pSource);

        // For create shader program
        static GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
};

#endif
