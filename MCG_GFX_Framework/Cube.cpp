#include "Cube.h"
#include "Ray.h"

Cube::Cube(glm::vec3 _pos, glm::vec3 _color, Material _mat, std::string _name, float _edge) : Object(_pos, _color, _mat, _name)
{
	edgeLength = _edge;
}

Cube::~Cube()
{

}

glm::vec3 Cube::Normal(glm::vec3 _point)
{
	return glm::vec3(0);
}

HitInfo Cube::HasIntersected(Ray _ray)
{
	HitInfo _info;

	return _info;
}

glm::vec3 Cube::Shade(Ray _ray, glm::vec3 _point)
{
	return glm::vec3(0);
}

glm::vec3 Cube::DiffuseShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light)
{
	return glm::vec3(0);
}