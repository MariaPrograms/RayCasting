#include "Object.h"
#include "Ray.h"


Object::Object(glm::vec3 _pos, Material _mat)
{
	centre = _pos;
	mat = _mat;
}