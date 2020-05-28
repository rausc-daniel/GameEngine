#pragma once
#include <GL/gl.h>

class Texture
{
public:
	GLuint handle;
	Texture(const char* filename);
	~Texture();
	int width, height;
private:
	GLuint Load(const char* filename, int* width, int* height);
};
