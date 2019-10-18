#include <GLM/glm.hpp>
#include <memory>
class Ray;

class Camera
{
public:
	Camera();
	~Camera();
	std::shared_ptr<Ray> GenerateRays(glm::ivec3 pixel);

private:
	glm::mat2x3 viewing;
	glm::vec3 position;
	
};


