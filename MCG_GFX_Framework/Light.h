#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "GLM/glm.hpp"


class Light
{
public:
	Light(glm::vec3 _color, float _intencity);
	~Light();
	glm::vec3 GetLightAmount() { return color * intencity; }

protected:
	glm::mat4 lightToWorld;
	glm::vec3 color;
	float intencity;
};

#endif // !LIGHT_H