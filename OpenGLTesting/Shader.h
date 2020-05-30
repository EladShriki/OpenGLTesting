#pragma once


#include <string>
#include <iostream>
#include <fstream>

#include <gl/glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile(const char* vertexPath, const char* fragmentPath);

	std::string ReadFile(const char* path);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntesityLocation();
	GLuint GetAmbientColorLocation();
	GLuint GetDiffuseIntesityLocation();
	GLuint GetDirectionLocation();


	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView, 
		uniformAmbientIntesity, uniformAmbientColor, uniformDiffuseIntesity, uniformDirection;

	void ComplieShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

