#include "Sphere.h"
#include "Ray.h"


Sphere::Sphere(glm::vec3 _pos, glm::vec3 _color, float _rad) : Object(_pos, _color)
{
	radius = _rad;
}


HitAndPoint Sphere::HasIntersected(Ray _ray)
{
	HitAndPoint rtn;
	rtn.hit = false;
	rtn.distance = glm::vec3(0, 0, 0);

	if ((_ray.GetOrgin().z <= centre.z + radius && _ray.GetOrgin().z >= centre.z - radius) &&
		(_ray.GetOrgin().x <= centre.x + radius && _ray.GetOrgin().x >= centre.x - radius) &&
		(_ray.GetOrgin().y <= centre.y + radius && _ray.GetOrgin().y >= centre.y - radius))
	{
		//std::cout << "Not valid circle to far" << std::endl;
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
	if (magnituedOfDistanceVector > radius || centre.z < _ray.GetOrgin().z)
	{
		
		return rtn;
	}

	//Geting the amount to go back for the forward itersection
	float x = glm::sqrt((radius * radius) - (magnituedOfDistanceVector * magnituedOfDistanceVector));
	scalerValue =- x;
	glm::vec3 distance = _ray.GetOrgin() + (scalerValue * _ray.GetDirection());

	rtn.hit = true;
	rtn.distance = distance;
	//std::cout << "Valid at (" << rtn.distance.x << ", " << rtn.distance.y << ", " << rtn.distance.z << ")" << std::endl;
	return rtn;
}