#include "Material.h"

Material::Material()
{
	this->specularIntesity = 0;
	this->shininess = 0;
}

Material::Material(GLfloat sIntesity, GLfloat shine) : specularIntesity(sIntesity), shininess(shine) {}

void Material::UseMaterial(GLuint specularIntesityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntesityLocation, this->specularIntesity);
	glUniform1f(shininessLocation, this->shininess);
}

Material::~Material()
{

}
