#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(glm::vec3 _pos, float _rad, Material _mat);
	HitInfo HasIntersected(Ray _ray);
	glm::vec3 Normal(glm::vec3 _point);
	glm::vec3 Shade(Ray _ray, glm::vec3 _point);
	glm::vec3 DiffuseShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light);

private:
	float radius;

};

