#include <GLM/glm.hpp>
#include <memory>

class Object;

struct HitInfo
{
	bool hit;
	float distance;
	glm::vec3 intersectPoint;
	std::shared_ptr<Object> object;
};

class Ray
{
public:
	Ray(glm::vec3 _origin, glm::vec3 _dirction);
	~Ray();
	glm::vec3 GetOrgin() { return origin; }
	glm::vec3 GetDirection() { return dirction; }

private:
	glm::vec3 origin;
	glm::vec3 dirction;
};


