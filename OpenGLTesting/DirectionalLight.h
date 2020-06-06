#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
		  GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
					GLuint diffuseIntesityLocation, GLuint directionLocation);


	~DirectionalLight();


private:
	glm::vec3 direction;
};

