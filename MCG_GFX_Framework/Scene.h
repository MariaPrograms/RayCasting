#include <vector>
#include <GLM/glm.hpp>

class Object;
class Camera;

class Scene
{
public:
	Scene();
	~Scene();
	void DrawScreen(Camera _cam, glm::vec2 _screenSpecs, std::vector<Object> _objects);

private:
	std::vector<Object> objects;
};

Scene::Scene()
{
}

Scene::~Scene()
{
}
