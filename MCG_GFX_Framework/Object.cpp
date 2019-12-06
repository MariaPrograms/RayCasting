#include "Object.h"
#include "Ray.h"


Object::Object(glm::vec3 _pos, glm::vec3 _color, Material _mat)
{
	centre = _pos;
	color = _color;
	mat = _mat;
}