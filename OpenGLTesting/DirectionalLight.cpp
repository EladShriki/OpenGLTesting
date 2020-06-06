#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0, -1.0, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
									GLfloat aIntensity,
									GLfloat xDir, GLfloat yDir, GLfloat zDir, 
									GLfloat dIntensity) : Light(red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
	GLuint diffuseIntesityLocation, GLuint directionLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntesityLocation, diffuseIntensity);
}

DirectionalLight::~DirectionalLight()
{

}