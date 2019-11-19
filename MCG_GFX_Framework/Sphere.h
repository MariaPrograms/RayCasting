#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(glm::vec3 _pos, glm::vec3 _color, float _rad);
	HitAndPoint HasIntersected(Ray _ray);
	glm::vec3 Normal(glm::vec3 _point);
	glm::vec3 Shade(Ray _ray, glm::vec3 _point);
	glm::vec3 DirectionLightShade(Ray _ray, glm::vec3 _point, DistanceLight _light);
	glm::vec3 DirectionLightShade(Ray _ray, glm::vec3 _point, PointLight _light);

private:
	float radius;

};

