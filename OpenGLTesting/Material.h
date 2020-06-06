#pragma once

#include <gl/glew.h>

class Material
{
public:
	Material();
	Material(GLfloat sIntesity, GLfloat shine);

	void UseMaterial(GLuint specularIntesityLocation, GLuint shininessLocation);

	~Material();

private:
	GLfloat specularIntesity;
	GLfloat shininess;
};

