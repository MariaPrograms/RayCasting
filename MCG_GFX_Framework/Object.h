#include <GLM/glm.hpp>

class Ray;
struct HitNDistance
{
	bool hit;
	glm::vec3 distance;

};

class Object
{
public:
	Object(glm::vec3 _color);
	~Object();
	glm::vec3 Normal (glm::vec3 _point);
	virtual HitNDistance HasIntersected(Ray _ray) = 0;

protected:
	glm::vec3 centre;
	glm::vec3 rotation;
	glm::vec3 color;
	glm::vec3 Shade(Ray _ray);
};
