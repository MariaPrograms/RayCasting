#include "Object.h"
#include "Ray.h"


Object::Object(glm::vec3 _pos, glm::vec3 _color, Material _mat)
{
	centre = _pos;
	color = _color;
	mat = _mat;
	albedo = glm::vec3(0.8f);
}

Object::~Object()
{
}



/*glm::vec3 Object::Shade(Ray _ray, glm::vec3 _point, Light _lightSorce)
{
	return color;
}*/


