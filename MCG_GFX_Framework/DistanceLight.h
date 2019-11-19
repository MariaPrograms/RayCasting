#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>

class DistanceLight : public Light
{
public:
	DistanceLight(glm::vec3 _color, float _intencity, glm::vec3 _direction);
	~DistanceLight();
	glm::vec3 GetDirection() { return direction; }
private:
	glm::vec3 direction;
};

