#include "Ray.h"

Ray::Ray(glm::vec3 _origin, glm::vec3 _dirction, int _depth)
{
	origin = _origin;
	dirction = _dirction;
	depth = _depth;
}