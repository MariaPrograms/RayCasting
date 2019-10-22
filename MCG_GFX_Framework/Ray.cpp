#include "Ray.h"

Ray::Ray(glm::vec3 _origin, glm::vec3 _dirction)
{
	origin = _origin;
	dirction = _dirction;
}

Ray::~Ray()
{
}