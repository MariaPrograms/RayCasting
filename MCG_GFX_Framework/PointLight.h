#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

class PointLight : public Light
{
public:
	PointLight(glm::vec3 _color, float _intencity, glm::vec3 _pos);
	~PointLight();
	void GetLightAmountNDirection(glm::vec3 _point, glm::vec3& _direction, glm::vec3& _lightAmount);

private:
	glm::vec3 pos;
};

