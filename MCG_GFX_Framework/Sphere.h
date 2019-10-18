#include "Object.h"

class Sphere : Object
{
public:
	HitNDistance HasIntersected(Ray _ray);

private:
	float radius;

};

