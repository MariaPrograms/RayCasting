#include "Camera.h"
#include "Ray.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

Ray Camera::GenerateRays(glm::vec2 pixel)
{
	glm::vec3 Origin = glm::vec3(pixel.x, pixel.y, 0);
	glm::vec3 Direction = glm::vec3(0, 0, -1);

	Ray ray = Ray(Origin, Direction);

	return  ray;
}