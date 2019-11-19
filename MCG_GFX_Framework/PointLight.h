#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>

class PointLight : public Light
{
public:
	PointLight(glm::vec3 _color, float _intencity, glm::vec3 _pos);
	~PointLight();
	void GetDirectionAndIntensity(const glm::vec3 &_point, glm::vec3 &_lightDir, glm::vec3 &lightIntensity);

private:
	glm::vec3 pos;
};

