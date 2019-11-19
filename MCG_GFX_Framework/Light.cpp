#include "Light.h"

Light::Light(glm::vec3 _color, float _intencity)
{
	color = _color;
	intencity = _intencity;
}

Light::~Light()
{
}