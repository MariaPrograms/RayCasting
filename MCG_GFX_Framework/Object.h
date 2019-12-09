#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <GLM/glm.hpp>
#include <memory>
#include <string>

class Ray;
class Light;
struct HitInfo;

enum MaterialType
{
	Basic,
	Diffuse,
	Refelctive,
	Refraction,
	RefelctiveNRefraction
};

struct Material
{
	glm::vec3 color;
	MaterialType type;
	float ior;

	void CheckCol()
	{
		if (color.x > 1 && color.y > 1 && color.z > 1)
		{
			color /= 255.0f;
		}
	}
};


class Object
{
public:
	Object(glm::vec3 _pos, Material _mat);

	virtual glm::vec3 Normal (glm::vec3 _point) = 0;
	virtual HitInfo HasIntersected(Ray _ray) = 0;

	virtual glm::vec3 Shade(Ray _ray, glm::vec3 _point) = 0;
	virtual glm::vec3 DiffuseShade(Ray _ray, glm::vec3 _point, std::shared_ptr<Light> _light) = 0;

	glm::vec3 GetColor() { return  mat.color * glm::vec3(255, 255, 255); }
	MaterialType GetMaterialType() { return  mat.type; }
	float GetIor() { return mat.ior; }

	std::shared_ptr<Object> self;

	//Testing
	void SetName(std::string _name) { name = _name; }
	std::string GetName() { return name; }

	

protected:
	glm::vec3 centre;

	Material mat;

	std::string name;
};

#endif // !OBJECT_H