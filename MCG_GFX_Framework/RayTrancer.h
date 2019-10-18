#include <GLM/glm.hpp>

class Ray;

class RayTracer
{
public:
	RayTracer();
	~RayTracer();
	glm::vec3 TraceRay(Ray _ray);

private:

};
