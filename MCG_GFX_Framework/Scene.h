#include <vector>
#include <GLM/glm.hpp>
#include <memory>

class Object;
class Camera;

class Scene
{
public:
	Scene(glm::ivec2 _windowSize);
	~Scene();
	void DrawScreen(Camera _cam, std::vector<std::shared_ptr<Object>> _objects);

private:
	glm::ivec2 windowSize;
	std::vector<Object> objects;
};
