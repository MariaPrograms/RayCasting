#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(glm::vec3 _pos, glm::vec3 _color, float _rad);
	HitAndPoint HasIntersected(Ray _ray);

private:
	float radius;

};

