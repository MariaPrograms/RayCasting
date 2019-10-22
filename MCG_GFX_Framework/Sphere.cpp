#include "Sphere.h"
#include "Ray.h"
#include <iostream>

Sphere::Sphere(glm::vec3 _pos, glm::vec3 _color, float _rad) : Object(_pos, _color)
{
	radius = _rad;
}


HitAndPoint Sphere::HasIntersected(Ray _ray)
{
	HitAndPoint rtn;
	rtn.hit = false;
	rtn.distance = glm::vec3(0, 0, 0);

	if (_ray.GetOrgin() == centre)
	{
		return rtn;
	}
	
	//Shortest Distance from Point to Line
	glm::vec3 OrginToCentre = centre - _ray.GetOrgin();//(𝑷−𝒂)
	float scalerValue = glm::dot(OrginToCentre, _ray.GetDirection()); //(𝑷−𝒂)⋅𝒏
	glm::vec3 shortestPoint = scalerValue * _ray.GetDirection(); //((𝑷−𝒂)⋅𝒏)𝒏 = X

	//Getting Distnace from X to P 
	glm::vec3 distanceVector = OrginToCentre - shortestPoint; // P - X || 𝑷−𝒂−((𝑷−𝒂)⋅𝒏)𝒏
	float magnituedOfDistanceVector = glm::length(distanceVector); // ‖𝑷−𝑿‖

	//Checks 
	//If the shortest distance is in the sphere 
	//Making sure its not behind the orgin or pointing away
	//std
	if (magnituedOfDistanceVector <= radius || distanceVector.x > _ray.GetOrgin().x || distanceVector.x > _ray.GetDirection().x )
	{
		return rtn;
	}

	//Geting the amount to go back for the forward itersection
	float x = glm::sqrt((radius * radius) - (magnituedOfDistanceVector * magnituedOfDistanceVector));
	scalerValue =- x;
	glm::vec3 distance = _ray.GetOrgin() + (scalerValue * _ray.GetDirection());

	rtn.hit = true;
	rtn.distance = distance;
	return rtn;
}