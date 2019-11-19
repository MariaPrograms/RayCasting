#include "PointLight.h"

PointLight::PointLight(glm::vec3 _color, float _intencity, glm::vec3 _pos) : Light( _color, _intencity)
{
	pos = _pos;
}

void PointLight::GetDirectionAndIntensity(const glm::vec3 &_point, glm::vec3 &_lightDir, glm::vec3 &lightIntensity)
{
	//_lightDir = pos - _point; // compute light direction 
	//float r2 = glm::normalize(_lightDir);
	//lightDir.normalize();
	//lightIntensity = intencity * color / (4 * glm::pi<float>() * r2);
}

PointLight::~PointLight()
{

}