﻿#include "Sphere.h"
#include "Ray.h"
#include "DistanceLight.h"
#include "PointLight.h"

#include <iostream>

Sphere::Sphere(glm::vec3 _pos, glm::vec3 _color, float _rad) : Object(_pos, _color)
{
	radius = _rad;
}

HitAndPoint Sphere::HasIntersected(Ray _ray)
{
	HitAndPoint rtn;
	rtn.hit = false;
	rtn.distance = 20000;
	rtn.intersectPoint = glm::vec3(0, 0, 0);
	
	//Shortest Distance from Point to Line
	glm::vec3 OrginToCentre = centre - _ray.GetOrgin();//(𝑷−𝒂)
	float scalerValue = glm::dot(OrginToCentre, _ray.GetDirection()); //(𝑷−𝒂)⋅𝒏
	glm::vec3 shortestPoint = _ray.GetOrgin() + scalerValue * _ray.GetDirection(); //((𝑷−𝒂)⋅𝒏)𝒏 = X

	//Getting Distnace from X to P 
	glm::vec3 distanceVector = OrginToCentre - shortestPoint; // P - X || 𝑷−𝒂−((𝑷−𝒂)⋅𝒏)𝒏
	float magnituedOfDistanceVector = glm::length(distanceVector); // ‖𝑷−𝑿‖

	//Checks 
	//If the shortest distance is in the sphere 
	//Making sure its not behind the orgin or pointing away
	if (magnituedOfDistanceVector > radius || scalerValue < 0.0f )
	{
		return rtn;
	}

	//Geting the amount to go back for the forward itersection
	float x = glm::sqrt((radius * radius) - (magnituedOfDistanceVector * magnituedOfDistanceVector));
	glm::vec3 distance = _ray.GetOrgin() + ((scalerValue - x) * _ray.GetDirection());

	rtn.hit = true;
	rtn.distance = glm::length(distance);
	rtn.intersectPoint = distance;
	return rtn;
}

glm::vec3 Sphere::Normal(glm::vec3 _point)
{
	return (_point - centre) * (1.0f / radius);
}

glm::vec3 Sphere::Shade(Ray _ray, glm::vec3 _point)
{
	float FR = glm::max(0.0f, glm::dot(Normal(_point), _ray.GetDirection()));
	glm::fvec3 smallcol = color * FR;
	return smallcol * glm::vec3(255);
}

glm::vec3 Sphere::DirectionLightShade(Ray _ray, glm::vec3 _point, DistanceLight _light)
{
	glm::vec3 L = _light.GetDirection();
	glm::vec3 hitCol = (albedo / glm::pi<float>()) * _light.GetLightAmount() * glm::vec3(glm::max(0.0f, glm::dot(Normal(_point), L)));
	return hitCol * glm::vec3(255);
}

glm::vec3 Sphere::DirectionLightShade(Ray _ray, glm::vec3 _point, PointLight _light)
{
	//glm::vec3 L = _light.GetDirection();
	//glm::vec3 hitCol = (albedo / glm::pi<float>()) * _light.GetLightAmount() * glm::vec3(glm::max(0.0f, glm::dot(Normal(_point), L)));
	//return hitCol * glm::vec3(255);
	return glm::vec3(255);
}
