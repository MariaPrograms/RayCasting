#include <vector>
#include <GLM/glm.hpp>
#include <memory>

class Camera;
class Light;
class Ray;
class Object;
struct HitInfo;

class Scene
{
public:
	Scene(glm::ivec2 _windowSize);
	~Scene();
	void DrawScreen(std::vector<std::shared_ptr<Object>> _objects, std::vector<std::shared_ptr<Light>> lights, int _screenSplitX, int _screenSplitY);
	
	

private:
	std::shared_ptr<Camera> camera;
	glm::ivec2 windowSize;
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Light>> lights;

	void DrawScreenPart(glm::vec2 _startPos, glm::vec2 _endPos);
	glm::vec3 GetColor(Ray _ray);
	HitInfo CheckRay(Ray _ray);

	bool InShadow(glm::vec3 _intersectPoint, std::shared_ptr<Object> _object);
	glm::vec3 Reflect(const glm::vec3 &_direction, const glm::vec3 &_normal);
};
