#pragma once
#include "Object.h"

class Plane : public Object
{
public:
	Plane(glm::vec3 _pos, glm::vec3 _direction, Material _mat);
	HitInfo HasIntersected(Ray _ray);
	glm::vec3 Normal(glm::vec3 _point);
	glm::vec3 Shade(Ray _ray, glm::vec3 _point);
	glm::vec3 DiffuseShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light);

private:
	glm::vec3 normal;
};

