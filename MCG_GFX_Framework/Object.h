#include <GLM/glm.hpp>

class Ray;
class Light;


struct HitAndPoint
{
	bool hit;
	glm::vec3 distance;
};

class Object
{
public:
	Object(glm::vec3 _pos, glm::vec3 _color);
	~Object();

	glm::vec3 Normal (glm::vec3 _point);
	virtual HitAndPoint HasIntersected(Ray _ray) = 0;

protected:

	glm::vec3 Shade(Ray _ray, glm::vec3 _point, Light _lightSorce);
	glm::vec3 centre;
	glm::vec3 rotation;
	glm::vec3 color;
};
