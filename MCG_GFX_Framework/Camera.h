#include <GLM/glm.hpp>
#include <memory>
class Ray;

class Camera
{
public:
	Camera();
	~Camera();
	Ray GenerateRays(glm::vec2 pixel);

private:
	glm::mat4x4 viewingMatrix;
	glm::mat4x4 projectionMatrix;
	glm::vec3 position;
	
};


