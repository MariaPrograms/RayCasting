#include "Plane.h"
#include "Ray.h"
#include "Light.h"
#include <iostream>


Plane::Plane(glm::vec3 _pos, glm::vec3 _normal, Material _mat) : Object(_pos, _mat)
{
	normal = _normal;
}

glm::vec3 Plane::Shade(Ray _ray, glm::vec3 _point)
{
	float FR = glm::dot(normal, -_ray.GetDirection());
	glm::fvec3 col = mat.color * FR;
	col = glm::clamp(col, glm::vec3(0), glm::vec3(1));
	return col * glm::vec3(255);
}

HitInfo Plane::HasIntersected(Ray _ray)
{
	HitInfo rtn;
	rtn.hit = false;
	rtn.distance = 20000;
	rtn.intersectPoint = glm::vec3(0, 0, 0);
	rtn.object = nullptr;

	float denominator = glm::dot(normal, _ray.GetDirection()); //l⋅n
	
	if (glm::abs(denominator) > 0.0001f)
	{
		glm::vec3 OrginToCentre = centre - _ray.GetOrgin();//p0−l0
		float dotProduct = glm::dot(OrginToCentre, normal); //(p0−l0)⋅n
		float t = dotProduct / denominator; //(p0−l0)⋅n / l⋅n

		if (t >= 0)
		{
			rtn.hit = true;
			rtn.intersectPoint = _ray.GetOrgin() + t * _ray.GetDirection();
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
	glm::vec3 hitCol = mat.color * glm::dot(normal, direction) * lightAmount;
	hitCol = glm::clamp(hitCol, glm::vec3(0), glm::vec3(1));
	return hitCol * glm::vec3(255);
}