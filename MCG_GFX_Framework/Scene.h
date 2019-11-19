#include <vector>
#include <GLM/glm.hpp>
#include <memory>

class Object;
class Camera;
class DistanceLight;

class Scene
{
public:
	Scene(glm::ivec2 _windowSize);
	~Scene();
	void DrawScreen(std::vector<std::shared_ptr<Object>> _objects, std::vector<DistanceLight> lights, int _screenSplitX, int _screenSplitY);
	void DrawScreenPart(glm::vec2 _startPos, glm::vec2 _endPos);

private:
	std::shared_ptr<Camera> camera;
	glm::ivec2 windowSize;
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<DistanceLight> lights;
};
