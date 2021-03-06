#include "Camera.h"
#include "Ray.h"
#include "Light.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec2 screenWidth)
{
	projectionMatrix = glm::perspective(0.7f, screenWidth.x / screenWidth.y, 1.0f, 100.0f);
	invProjectionMatrix = glm::inverse(projectionMatrix);

	widthRange = screenWidth.x;
	heightRange = screenWidth.y;
}

Ray Camera::GenerateScreenRay(glm::vec2 pixel)
{
	float range2 = 2;
	float minimum2 = -1;

	float ndcXPoint = pixel.x * range2 / widthRange + minimum2;
	float ndcYPoint = (pixel.y * range2 / heightRange + minimum2) * -1;

	glm::vec4 ndcNearPlanePoint = glm::vec4(ndcXPoint, ndcYPoint, -1, 1);
	glm::vec4 ndcFarPlanePoint = glm::vec4(ndcXPoint, ndcYPoint, 1, 1);

	glm::vec4 nearEyeSpacePoint = invProjectionMatrix * ndcNearPlanePoint;
	glm::vec4 farEyeSpacePoint = invProjectionMatrix * ndcFarPlanePoint;

	glm::vec3 nearRightHandedPoint = nearEyeSpacePoint / nearEyeSpacePoint.w;
	glm::vec3 farRightHandedPoint = farEyeSpacePoint / farEyeSpacePoint.w;

	glm::vec3 direction = farRightHandedPoint - nearRightHandedPoint;

	Ray ray = Ray(nearRightHandedPoint, glm::normalize(direction), 0);
	return  ray;
}