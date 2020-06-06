#pragma once

#include <gl/glew.h>
#include <SOIL.h>
#include <stdio.h>

class Texture
{

public:
	Texture();
	Texture(const char* path);

	bool LoadTexture();
	bool LoadTextureA();

	void UseTexture();
	void ClearTexture();

	
	~Texture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	char *fileLocation;
};

