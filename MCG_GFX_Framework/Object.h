#include <GLM/glm.hpp>
#include <glm/gtc/constants.hpp>

class Ray;
class DistanceLight;
class PointLight;

struct HitAndPoint
{
	bool hit;
	float distance;
	glm::vec3 intersectPoint;
};

class Object
{
public:
	Object(glm::vec3 _pos, glm::vec3 _color);
	~Object();

	virtual glm::vec3 Normal (glm::vec3 _point) = 0;
	virtual HitAndPoint HasIntersected(Ray _ray) = 0;
	virtual glm::vec3 Shade(Ray _ray, glm::vec3 _point) = 0;
	virtual glm::vec3 DirectionLightShade(Ray _ray, glm::vec3 _point, DistanceLight _light) = 0;
	virtual glm::vec3 DirectionLightShade(Ray _ray, glm::vec3 _point, PointLight _light) = 0;
	glm::vec3 GetColor() { return  color * glm::vec3(255, 255, 255); }

protected:
	glm::vec3 centre;
	glm::vec3 rotation;
	glm::vec3 color;
	glm::vec3 albedo;
};
