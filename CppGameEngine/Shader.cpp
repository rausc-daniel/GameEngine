#include "Shader.h"
#include <cstdio>
#include <fstream>

Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader) {
    program = glCreateProgram();
    glAttachShader(program, CreateShader(GL_VERTEX_SHADER, vertexShader));
    glAttachShader(program, CreateShader(GL_FRAGMENT_SHADER, fragmentShader));
    //glBindAttribLocation(program, 0, "in_Position");
    glLinkProgram(program);

    char buffer[1000];
    int length;
    glGetProgramInfoLog(program, 1000, &length, buffer);
    printf("%s", buffer);

    auto error = glGetError();
    if (error != GL_NO_ERROR)
        throw error;
}

int Shader::CreateShader(GLuint type, const std::string &shaderCode) {
    const char *code = shaderCode.c_str();
    GLuint vertexOrFragmentShader = glCreateShader(type);
    glShaderSource(vertexOrFragmentShader, 1, &code, NULL);
    glCompileShader(vertexOrFragmentShader);
    GLint status;
    glGetShaderiv(vertexOrFragmentShader, GL_COMPILE_STATUS, &status);
    //TODO: add better error handling, wallShader was crashing with no error
    if (status == 0) {
        char buffer[1000];
        int length;
        glGetShaderInfoLog(vertexOrFragmentShader, 1000, &length, buffer);
        printf("%s", buffer);
        throw buffer;
    }
    return vertexOrFragmentShader;
}

void Shader::Use() const {
    glUseProgram(program);
}

std::shared_ptr<Shader> Shader::Load(const std::string &fileName) {
    std::string vert = GetFileText(fileName + ".vert");
    std::string frag = GetFileText(fileName + ".frag");

    return std::make_shared<Shader>(vert, frag);
}

std::string Shader::GetFileText(const std::string &fileName) {
    std::ifstream stream(fileName);
    return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}
