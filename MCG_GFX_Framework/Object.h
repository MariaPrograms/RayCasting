#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <GLM/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <memory>
#include <string>

class Ray;
class Light;

enum Material
{
	Basic,
	Diffuse,
	Refelctive,
	Refraction
}; 

struct HitInfo;

class Object
{
public:
	Object(glm::vec3 _pos, glm::vec3 _color, Material _mat);

	virtual glm::vec3 Normal (glm::vec3 _point) = 0;
	virtual HitInfo HasIntersected(Ray _ray) = 0;

	virtual glm::vec3 Shade(Ray _ray, glm::vec3 _point) = 0;
	virtual glm::vec3 DiffuseShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light) = 0;
	
	float GetIor() { return ior; }
	void SetIor(float _value) { ior = _value; }

	glm::vec3 GetColor() { return  color * glm::vec3(255, 255, 255); }
	Material GetMaterial() { return  mat; }

	void SetName(std::string _name) { name = _name; }
	std::string GetName() { return name; }

	std::shared_ptr<Object> self;

protected:
	glm::vec3 centre;
	glm::vec3 rotation;

	Material mat;
	glm::vec3 color;
	float ior;

	std::string name;
};

#endif // !OBJECT_H