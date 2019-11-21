#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <iostream>
#include "MCG_GFX_Lib.h"

class PointLight : public Light
{
public:
	PointLight(glm::vec3 _color, float _intencity, glm::vec3 _pos);
	~PointLight();
	void GetLightAmountNDirection(glm::vec3 _point, glm::vec3& _direction, glm::vec3& _lightAmount);
	glm::vec3 GetDirection(glm::vec3 _point);

private:
	glm::vec3 pos;
	glm::vec3 test;
};

