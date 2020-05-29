#pragma once

#include <GL/gl.h>
#include <string>

class Texture {
public:
    explicit Texture(const char *filename);
    ~Texture();

    GLuint handle;
    int width{};
    int height{};
private:
    static GLuint Load(std::string filename, int *width, int *height);
};
