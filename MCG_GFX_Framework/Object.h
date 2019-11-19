#include <GLM/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <memory>

class Ray;
class Light;

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
	virtual glm::vec3 LightShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light) = 0;
	glm::vec3 GetColor() { return  color * glm::vec3(255, 255, 255); }

protected:
	glm::vec3 centre;
	glm::vec3 rotation;
	glm::vec3 color;
	glm::vec3 albedo;
};
