#include <GLM/glm.hpp>

class Ray;
class Light;


struct HitAndPoint
{
	bool hit;
	float distance;
};

class Object
{
public:
	Object(glm::vec3 _pos, glm::vec3 _color);
	~Object();

	glm::vec3 Normal (glm::vec3 _point);
	virtual HitAndPoint HasIntersected(Ray _ray) = 0;
	glm::vec3 GetColor() { return  color * glm::vec3(255, 255, 255); }

protected:

	glm::vec3 Shade(Ray _ray, glm::vec3 _point, Light _lightSorce);
	glm::vec3 centre;
	glm::vec3 rotation;
	glm::vec3 color;
};
