#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

class Shader {
public:
    Shader(const char *vertexShader, const char *fragmentShader);

    static int CreateShader(GLuint type, const char *&vertexShaderCode);

    void Use() const;

    int GetHandle() const { return program; }

private:
    GLuint program;
};
