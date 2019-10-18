#include "Sphere.h"
#include "Ray.h"

HitNDistance Sphere::HasIntersected(Ray _ray)
{
	HitNDistance rtn;
	rtn.hit = false;

	if (_ray.GetOrgin() == centre)
	{
		return rtn;
	}

	glm::vec3 AB = centre - _ray.GetOrgin();
	float AC = glm::dot(AB, _ray.GetDirection());
	glm::vec3 AD = AC * _ray.GetDirection();
	glm::vec3 point = _ray.GetOrgin() + AD;



	   
}