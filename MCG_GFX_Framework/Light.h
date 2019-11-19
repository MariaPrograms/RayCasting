#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "GLM/glm.hpp"


class Light
{
public:
	Light(glm::vec3 _color, float _intencity);
	~Light();
	virtual void GetLightAmountNDirection(glm::vec3 _point, glm::vec3& _direction, glm::vec3& _lightAmount) = 0;

protected:
	glm::mat4 lightToWorld;
	glm::vec3 color;
	float intencity;
};

#endif // !LIGHT_H