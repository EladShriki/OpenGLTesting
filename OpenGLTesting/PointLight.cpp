#include "PointLight.h"


PointLight::PointLight() : Light()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->constant = 1.0f;
	this->linear = 0.0f;
	this->exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, 
						GLfloat aIntensity, GLfloat dIntensity,
						GLfloat xPos, GLfloat yPos, GLfloat zPos, 
						GLfloat con, GLfloat lin, GLfloat exp) : Light(red, green, blue, aIntensity, dIntensity)
{
	this->position = glm::vec3(xPos, yPos, zPos);
	this->constant = con;
	this->linear = lin;
	this->exponent = exp;
}


void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
							GLuint diffuseIntesityLocation, GLuint PositionLocation,
							GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntesityLocation, diffuseIntensity);

	glUniform3f(PositionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}


PointLight::~PointLight()
{

}