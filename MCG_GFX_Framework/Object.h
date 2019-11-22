#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <GLM/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <memory>

class Ray;
class Light;

enum Material
{
	Basic,
	Diffuse,
	Refelctive,
	Refraction,
	Fresnel
}; 

struct HitInfo;

class Object
{
public:
	

	Object(glm::vec3 _pos, glm::vec3 _color, Material _mat);
	~Object();

	virtual glm::vec3 Normal (glm::vec3 _point) = 0;
	virtual HitInfo HasIntersected(Ray _ray) = 0;
	virtual glm::vec3 Shade(Ray _ray, glm::vec3 _point) = 0;
	virtual glm::vec3 DiffuseShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light) = 0;
	glm::vec3 GetColor() { return  color * glm::vec3(255, 255, 255); }
	Material GetMaterial() { return  mat; }
	std::shared_ptr<Object> self;

protected:
	glm::vec3 centre;
	glm::vec3 rotation;
	glm::vec3 color;
	glm::vec3 albedo;
	Material mat;
};

#endif // !OBJECT_H