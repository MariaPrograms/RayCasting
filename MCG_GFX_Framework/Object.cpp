#include "Object.h"
#include "Ray.h"

Object::Object(glm::vec3 _pos, glm::vec3 _color)
{
	centre = _pos;
	color = _color;
}

Object::~Object()
{
}

glm::vec3 Object::Shade(Ray _ray)
{
	return color;
}


