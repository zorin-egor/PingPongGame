#include <stdlib.h>

#include "Common/LogGL.h"
#include "MakeShaders.h"

const char * MakeShaders::v_main_shader =   "attribute vec4 a_Position;"
                                            "attribute vec2 a_Texture;"
                                            "varying vec2 v_Texcoord;"
                                            "uniform mat4 u_Matrix;"
                                            "void main(){"
                                            "   v_Texcoord = a_Texture;"
                                            "   gl_Position = u_Matrix * a_Position;"
                                            "}";

const char * MakeShaders::f_main_shader =   "precision mediump float;"
                                            "uniform sampler2D u_Texture;"
                                            "varying vec2 v_Texcoord;"
                                            "void main(){"
                                            "   gl_FragColor = texture2D(u_Texture, v_Texcoord);"
                                            "}";

const char * MakeShaders::v_point_shader =  "attribute vec2 a_RandomArrayCoords;"
                                            "attribute float a_RandomArraySpeed;"
                                            "attribute float a_RandomArrayRadius;"
                                            "attribute float a_Delta;"
                                            "attribute vec4 a_ColorStart;"
                                            "attribute vec4 a_ColorEnd;"
                                            "uniform vec2 u_Size;"
                                            "uniform float u_TotalDeltaSpeed;"
                                            "varying vec4 v_Color;"
                                            "void main(){"
                                            "   float x_coord = a_RandomArrayCoords.x + a_RandomArrayRadius * cos(a_RandomArraySpeed + u_TotalDeltaSpeed);"
                                            "   float y_coord = 0.2 * sin(a_RandomArraySpeed + u_TotalDeltaSpeed) + a_RandomArrayCoords.y;"
                                            "   v_Color = mix(a_ColorStart, a_ColorEnd, a_Delta);"
                                            "   gl_PointSize = mix(u_Size.x, u_Size.y, a_Delta);"
                                            "   gl_Position = vec4(x_coord, y_coord, 1.0, 1.0);"
                                            "}";

const char * MakeShaders::f_point_shader =  "precision mediump float;"
                                            "varying vec4 v_Color;"
                                            "uniform sampler2D t_texture;"
                                            "void main(){"
                                            "    gl_FragColor = v_Color * texture2D(t_texture, gl_PointCoord);"
                                            "}";

const char * MakeShaders::v_splash_shader = "attribute vec2 a_ArrayCoords;"
                                            "attribute vec4 a_ColorStart;"
                                            "attribute vec4 a_ColorEnd;"
                                            "attribute float a_Delta;"
                                            "uniform vec2 u_Size;"
                                            "varying vec4 v_Color;"
                                            "void main(){"
                                            "   v_Color = mix(a_ColorStart, a_ColorEnd, a_Delta);"
                                            "   gl_PointSize = mix(u_Size.x, u_Size.y, a_Delta);"
                                            "   gl_Position = vec4(a_ArrayCoords, 1.0, 1.0);"
                                            "}";

const char * MakeShaders::f_splash_shader = "precision mediump float;"
                                            "varying vec4 v_Color;"
                                            "uniform sampler2D t_texture;"
                                            "void main(){"
                                            "    gl_FragColor = v_Color * texture2D(t_texture, gl_PointCoord);"
                                            "}";

GLuint MakeShaders::compileShader(GLenum shaderType, const char* pSource) {
    // Создаём шейдер и получаем ссылку него, где shaderType - тип шейдера
    GLuint shader = glCreateShader(shaderType);

    if(shader){
        // Привязываем шейдер к исходнику
        glShaderSource(shader, 1, &pSource, NULL);
        // Компилим шейдер
        glCompileShader(shader);
        GLint compiled = 0;
        // Проверяем статус компиляции шейдера
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        // Если скомпилить не удалось, то выводим полный лог и удаляем шейдер который создали
        if (compiled == 0) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char * buf = (char *) malloc(infoLen);
                if(buf){
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint MakeShaders::createProgram(const char* pVertexSource, const char* pFragmentSource) {
    // Компилим пару шейдеров "vertex" и "fragment"
    // Компилим "vertex" шейдер
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, pVertexSource);
    if (vertexShader == 0) {
        return 0;
    }

    // Компилим "fragment" шейдер
    GLuint pixelShader = compileShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (pixelShader == 0) {
        return 0;
    }

    // Создаем программу и получаем ссылку на неё
    GLuint program = glCreateProgram();
    if (program) {
        // Привязываем шейдеры к программе
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);

        // Линкуем программу
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        // Если не удалось слинковать, получаем статус и удаляем программу
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char * buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program: \n%s\n", buf);
                    free(buf);
                }
            }

            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}