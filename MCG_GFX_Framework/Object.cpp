#include "Object.h"
#include "Ray.h"

Object::Object(glm::vec3 _color)
{
}

Object::~Object()
{
}

glm::vec3 Object::Shade(Ray _ray)
{
	return color;
}


