#include "Plane.h"
#include "Ray.h"
#include "Light.h"
#include <iostream>


Plane::Plane(glm::vec3 _pos, glm::vec3 _color, Material _mat, glm::vec3 _normal) : Object(_pos, _color, _mat)
{
	normal = glm::normalize(_normal);
}

Plane::~Plane()
{


}

glm::vec3 Plane::Shade(Ray _ray, glm::vec3 _point)
{
	//float FR = glm::dot(Normal(_point), -_ray.GetDirection());
	//glm::fvec3 col = color * FR;
	//col = glm::clamp(col, glm::vec3(0), glm::vec3(1));
	return color * glm::vec3(255);
}

HitInfo Plane::HasIntersected(Ray _ray)
{
	HitInfo rtn;
	rtn.hit = false;
	rtn.distance = 20000;
	rtn.intersectPoint = glm::vec3(0, 0, 0);
	rtn.object = nullptr;

	float denom = glm::dot(normal, _ray.GetDirection());
	
	if (glm::abs(denom) > 0.0001f)
	{
		glm::vec3 difference = centre - _ray.GetOrgin();
		float t = glm::dot(difference, normal) / denom;
		//std::cout << t << std::endl;
		if (t >= 0)
		{
			rtn.hit = true;
			rtn.intersectPoint = (_ray.GetOrgin() + _ray.GetDirection()) * t;
			rtn.distance = glm::length(rtn.intersectPoint);
			rtn.object = self;
		}
	}

	return rtn;
}

glm::vec3 Plane::Normal(glm::vec3 _point)
{
	return normal;
}

glm::vec3 Plane::DiffuseShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light)
{
	glm::vec3 direction, lightAmount;
	_light->GetLightAmountNDirection(_point, direction, lightAmount);
	glm::vec3 hitCol = color * glm::dot(normal, direction) * lightAmount;
	hitCol = glm::clamp(hitCol, glm::vec3(0), glm::vec3(1));
	return hitCol * glm::vec3(255);
}