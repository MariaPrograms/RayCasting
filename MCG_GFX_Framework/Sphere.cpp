﻿#include "Sphere.h"
#include "Ray.h"

#include <iostream>
#include <algorithm> 

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
	return (_point - centre) * (-1 / radius);
}

glm::vec3 Sphere::Shade(Ray _ray, glm::vec3 _point)
{
	glm::vec3 N = Normal(_point);
	glm::vec3 V = glm::normalize((_ray.GetDirection()));

	float FR = std::max(0.0f, glm::dot(N, V));

	glm::fvec3 smallcol = color * (FR * 0.5f);

	return smallcol * glm::vec3(255, 255, 255);
}
