#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>

class DistanceLight : public Light
{
public:
	DistanceLight(glm::vec3 _color, float _intencity, glm::vec3 _direction);
	~DistanceLight();
	glm::vec3 GetDirection() { return direction; }
	void GetLightAmountNDirection(glm::vec3 _point, glm::vec3& _direction, glm::vec3& _lightAmount);

private:
	glm::vec3 direction;
};

