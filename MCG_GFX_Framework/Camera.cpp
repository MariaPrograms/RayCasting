#include "Camera.h"
#include "Ray.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec2 screenWidth)
{
	projectionMatrix = glm::perspective(0.7f, screenWidth.x / screenWidth.y, 1.0f, 100.0f);
	//viewMatrix  = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0,0,-1), glm::vec3(0, 1, 0));
	invProjectionMatrix = glm::inverse(projectionMatrix);
	//invViewMatrix = glm::inverse(viewMatrix);
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

	glm::vec4 ndcNearPlanePoint = glm::vec4(ndcXPoint, ndcYPoint, -1, 1);
	glm::vec4 ndcFarPlanePoint = glm::vec4(ndcXPoint, ndcYPoint, 1, 1);

	glm::vec4 nearEyeSpacePoint = invProjectionMatrix * ndcNearPlanePoint;
	glm::vec4 farEyeSpacePoint = invProjectionMatrix * ndcFarPlanePoint;

	glm::vec3 nearRightHandedPoint = nearEyeSpacePoint / nearEyeSpacePoint.w;
	glm::vec3 farRightHandedPoint = farEyeSpacePoint / farEyeSpacePoint.w;

	//glm::vec3 origin = invViewMatrix * nearRightHandedPoint;
	//glm::vec3 farWorldSpacePoint = invViewMatrix * farRightHandedPoint;

	glm::vec3 direction = farRightHandedPoint - nearRightHandedPoint;

	Ray ray = Ray(nearRightHandedPoint, glm::normalize(direction));
	return  ray;
}