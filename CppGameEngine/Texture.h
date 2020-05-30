#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <string>

class Texture {
public:
    explicit Texture(const char *fileName);

    ~Texture();

    GLuint handle;
    int width{};
    int height{};
private:
    static GLuint Load(std::string fileName, int *width, int *height);
};

#endif