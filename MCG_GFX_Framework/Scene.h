#include <vector>
#include <GLM/glm.hpp>
#include <memory>

class Camera;
class Light;
class Ray;
class Object;
class ThreadPool;
struct HitInfo;
struct Material;

class Scene
{
public:
	Scene(glm::ivec2 _windowSize);
	void DrawScreen(int _screenSplitX, int _screenSplitY);

	//Setting The scene functions
	void AddSphere(glm::vec3 _point, Material _mat, float _size);
	void AddPlane(glm::vec3 _point, glm::vec3 direction, Material _mat);
	void AddDistantLight(glm::vec3& _color, float _intencity, glm::vec3& _direction);
	void AddPointLight(glm::vec3& _color, float _intencity, glm::vec3& _pos);

	void SetBackgroundColor(glm::vec3 _color) { backgroundColor = _color; }

private:
	std::shared_ptr<Camera> camera;
	glm::ivec2 windowSize;
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Light>> lights;
	glm::vec3 backgroundColor;

	void DrawScreenPart(glm::vec2 _startPos, glm::vec2 _endPos);
	glm::vec3 GetColor(Ray _ray);
	HitInfo SendRay(Ray _ray);

	glm::vec3 InShadow(HitInfo _info, int _light);
	glm::vec3 Reflect(const glm::vec3 _direction, const glm::vec3 _normal);
	glm::vec3 Refract(const glm::vec3 _direction, const glm::vec3 _normal, const float ior);
	float Fresnel(const glm::vec3 I, const glm::vec3 N, const float ior);
};
