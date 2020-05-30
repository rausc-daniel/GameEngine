#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <memory>

class Shader {
public:
    Shader(const std::string &vertexShader, const std::string &fragmentShader);

    static std::shared_ptr<Shader> Load(const std::string &fileName);

    static int CreateShader(GLuint type, const std::string &shaderCode);

    void Use() const;

    int GetHandle() const { return program; }

private:
    GLuint program;

    static std::string GetFileText(const std::string &fileName);
};

#endif