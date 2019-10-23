#include "Camera.h"
#include "Ray.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec2 screenWidth)
{
	projectionMatrix = glm::perspective(0.7f, screenWidth.x / screenWidth.y, 1.0f, 100.0f);
	invProjectionMatrix = glm::inverse(projectionMatrix);
	widthRange = screenWidth.x;
	heightRange = screenWidth.y;
}

Camera::~Camera()
{
}

Ray Camera::GenerateRays(glm::vec2 pixel)
{
	float range2 = 2;
	float minimum2 = -1;

	float ndcXPoint = pixel.x * 2 / widthRange - 1;
	float ndcYPoint = (pixel.y * 2 / heightRange - 1) * -1;

	glm::vec4 point1 = glm::vec4(ndcXPoint, ndcYPoint, -1, 0);
	glm::vec4 point2 = glm::vec4(ndcXPoint, ndcYPoint, 1, 0);

	glm::vec4 transformedPoint1 = invProjectionMatrix * point1;
	glm::vec4 transformedPoint2 = invProjectionMatrix * point2;

	glm::vec3 Origin = transformedPoint1 / transformedPoint1.w;

	glm::vec3 point2vec = transformedPoint2 / transformedPoint2.w;

	glm::vec3 Direction = Origin - point2vec;

	Ray ray = Ray(glm::normalize(Origin), glm::normalize(Direction));
	return  ray;
}