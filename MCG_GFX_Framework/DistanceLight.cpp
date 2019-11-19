#include "DistanceLight.h"

DistanceLight::DistanceLight(glm::vec3 _color, float _intencity, glm::vec3 _direction) : Light(_color, _intencity)
{
	direction = glm::normalize(_direction);
}

DistanceLight::~DistanceLight()
{

}