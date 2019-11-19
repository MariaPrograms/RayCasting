#include "PointLight.h"


PointLight::PointLight(glm::vec3 _color, float _intencity, glm::vec3 _pos) : Light( _color, _intencity)
{
	pos = _pos;
}


PointLight::~PointLight()
{

}

void PointLight::GetLightAmountNDirection(glm::vec3 _point, glm::vec3& _direction, glm::vec3& _lightAmount)
{
	glm::vec3 lightDir = pos - _point; //compute light direction 
	float r2 = glm::l1Norm(lightDir);
	_direction = glm::normalize(lightDir);
	float area = 4 * glm::pi<float>() * r2;
	_lightAmount = intencity * color;
}