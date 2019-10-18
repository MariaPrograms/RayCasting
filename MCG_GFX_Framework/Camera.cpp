#include "Camera.h"
#include "Ray.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

std::shared_ptr<Ray> Camera::GenerateRays(glm::ivec3 pixel)
{
	std::shared_ptr<Ray> ray = std::make_shared<Ray>();
	return  ray;
}