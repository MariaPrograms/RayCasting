#include "PointLight.h"


PointLight::PointLight(glm::vec3 _color, float _intencity, glm::vec3 _pos) : Light( _color, _intencity)
{	
	pos = _pos;
	test = _pos;
}


PointLight::~PointLight()
{

}

void PointLight::GetLightAmountNDirection(glm::vec3 _point, glm::vec3& _direction, glm::vec3& _lightAmount)
{
	_direction = glm::normalize(GetDirection(_point)); //compute light direction
	float r2 = glm::length2(_direction);
	_lightAmount = intencity * color / r2;// / area;
}

glm::vec3 PointLight::GetDirection(glm::vec3 _point)
{
	glm::vec3 dis = pos - _point;
	dis = glm::normalize(dis);
	return dis;
}