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
	Ray(const glm::vec3 _origin, glm::vec3 _dirction, int _depth);
	const glm::vec3 GetOrgin() { return origin; } 
	const glm::vec3 GetDirection() { return dirction; }
	const int GetDepth() { return depth; }

private:
	glm::vec3 origin;
	glm::vec3 dirction;
	int depth;
};


