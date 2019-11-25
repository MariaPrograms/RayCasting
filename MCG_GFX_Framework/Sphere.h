#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(glm::vec3 _pos, glm::vec3 _color, Material _mat, std::string _name, float _rad);
	HitInfo HasIntersected(Ray _ray);
	glm::vec3 Normal(glm::vec3 _point);
	glm::vec3 Shade(Ray _ray, glm::vec3 _point);
	glm::vec3 DiffuseShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light);
	glm::vec3 ReflectiveShade(Ray _ray, glm::vec3 _point);

private:
	float radius;

};

