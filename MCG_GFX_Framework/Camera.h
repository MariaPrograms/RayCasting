#include <GLM/glm.hpp>
#include <memory>

class Ray;
class Light;

class Camera
{
public:
	Camera(glm::vec2 screenWidth);
	~Camera();
	Ray GenerateScreenRay(glm::vec2 pixel);
	Ray SpecificRay(glm::vec3 _origin, glm::vec3 _direction);

private:
	glm::mat4x4 viewMatrix;
	glm::mat4x4 projectionMatrix;
	glm::mat4x4 invProjectionMatrix;
	glm::mat4x4 invViewMatrix;
	glm::vec3 position;

	float widthRange;
	float heightRange;
};


