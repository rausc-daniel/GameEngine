#include "Shader.h"
#include <stdio.h>

Shader::Shader(const char* vertexShaderCode, const char* fragmentShaderCode)
{
    program = glCreateProgram();
    glAttachShader(program, CreateShader(GL_VERTEX_SHADER, vertexShaderCode));
    glAttachShader(program, CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode));
    glBindAttribLocation(program, 0, "in_Position");
    glLinkProgram(program);

    char buffer[1000];
    int length;
    glGetProgramInfoLog(program, 1000, &length, buffer);
    printf(buffer);

    auto error = glGetError();
    if (error != GL_NO_ERROR)
        throw error;
}

int Shader::CreateShader(GLuint type, const char * &vertexOrFragmentShaderCode)
{
    GLuint vertexOrFragmentShader = glCreateShader(type);
    glShaderSource(vertexOrFragmentShader, 1, &vertexOrFragmentShaderCode, NULL);
    glCompileShader(vertexOrFragmentShader);
    GLint status;
    glGetShaderiv(vertexOrFragmentShader, GL_COMPILE_STATUS, &status);
    //TODO: add better error handling, wallShader was crashing with no error
    if (status == false)
    {
        char buffer[1000];
        int length;
        glGetShaderInfoLog(vertexOrFragmentShader, 1000, &length, buffer);
        printf(buffer);
        throw buffer;
    }
    return vertexOrFragmentShader;
}

void Shader::Use()
{
    glUseProgram(program);
}
