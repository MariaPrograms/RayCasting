#include "Object.h"

class Cube : public Object
{
public:
	Cube(glm::vec3 _pos, glm::vec3 _color, Material _mat, std::string _name, float _edge);
	~Cube();
	glm::vec3 Normal(glm::vec3 _point);
	HitInfo HasIntersected(Ray _ray);
	glm::vec3 Shade(Ray _ray, glm::vec3 _point);
	glm::vec3 DiffuseShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light);

private:
	float edgeLength;
};

