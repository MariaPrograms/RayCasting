#include "MCG_GFX_Lib.h"
#include <iostream>
#include <thread>

#include "Scene.h"
#include "Camera.h"
#include "Object.h"
#include "Ray.h"
#include "DistanceLight.h"
#include "PointLight.h"
#include "ThreadPool.h"

#include "Sphere.h"
#include "Plane.h"

Scene::Scene(glm::ivec2 _windowSize)
{
	windowSize = _windowSize;
	camera = std::make_shared<Camera>(_windowSize);

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if (!MCG::Init(windowSize))
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return;
	}
	
	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground(glm::ivec3(0, 0, 0));
	backgroundColor = glm::vec3(0);
}

void Scene::AddSphere(glm::vec3 _point, Material _mat, float _size)
{
	_mat.CheckCol();
	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(_point, _size, _mat);
	sphere->self = sphere;
	objects.push_back(sphere);
}

void Scene::AddPlane(glm::vec3 _point, glm::vec3 direction, Material _mat)
{
	_mat.CheckCol();
	std::shared_ptr<Plane> plane = std::make_shared<Plane>(_point, direction, _mat);
	plane->self = plane;
	objects.push_back(plane);
}

void Scene::AddDistantLight(glm::vec3& _color, float _intencity, glm::vec3& _direction)
{
	std::shared_ptr<DistanceLight> light = std::make_shared<DistanceLight>(_color, _intencity, _direction);
	lights.push_back(light);
}

void Scene::AddPointLight(glm::vec3& _color, float _intencity, glm::vec3& _pos)
{
	std::shared_ptr<PointLight> light = std::make_shared<PointLight>(_color, _intencity, _pos);
	lights.push_back(light);
}

void Scene::DrawScreen(int _screenSplitX, int _screenSplitY)
{
	ThreadPool pool{ (size_t)(_screenSplitX  * _screenSplitY) };
	int widthToCheck = windowSize.x / _screenSplitX;
	int hightToCheck = windowSize.y / _screenSplitY;

	for (int x = 0; x < _screenSplitX; x++)
	{
		for (int y = 0; y < _screenSplitY; y++)
		{
			glm::vec2 startpos(widthToCheck * x, hightToCheck * y);
			glm::vec2 endpos(widthToCheck * (x + 1), hightToCheck * (y + 1));

			pool.AddToQueue([this, startpos, endpos]
			{
				DrawScreenPart(startpos, endpos);
			});
		}
	}

	pool.~ThreadPool();
}

void Scene::DrawScreenPart(glm::vec2 _startPos, glm::vec2 _endPos)
{
	glm::ivec2 pixelPosition;
	glm::ivec3 pixelColour;

	for (int x = _startPos.x; x < _endPos.x; x++)
	{
		for (int y = _startPos.y; y < _endPos.y; y++)
		{
			pixelPosition = glm::ivec2(x, y);
			Ray ray = camera->GenerateScreenRay(glm::vec2(x, y));
			pixelColour = GetColor(ray);
			MCG::DrawPixel(pixelPosition, pixelColour);
		}
	}
}

glm::vec3 Scene::GetColor(Ray _ray)
{
	glm::vec3 pixelColour(0);

	if (_ray.GetDepth() < 3)
	{

		HitInfo hitInfo = SendRay(_ray);

		if (hitInfo.hit)
		{
			switch (hitInfo.object->GetMaterialType())
			{
			case Basic:
				pixelColour = hitInfo.object->Shade(_ray, hitInfo.intersectPoint);
				break;

			case Diffuse:
				for (int i = 0; i < lights.size(); i++)
				{
					pixelColour += hitInfo.object->DiffuseShade(_ray, hitInfo.intersectPoint, lights.at(i)) * InShadow(hitInfo, i);
				}
				break;

			case Refelctive:
			{
				glm::vec3 hitNormal = hitInfo.object->Normal(hitInfo.intersectPoint);
				glm::vec3 reflectedDirection = Reflect(_ray.GetDirection(), hitNormal);
				reflectedDirection = glm::normalize(reflectedDirection);
				Ray reflectRay = Ray(hitInfo.intersectPoint + reflectedDirection * 0.01f, reflectedDirection, _ray.GetDepth() + 1);
				pixelColour += glm::vec3(0.8) * GetColor(reflectRay);
				break;
			}
			case Refraction:
			{
				glm::vec3 hitNormal = hitInfo.object->Normal(hitInfo.intersectPoint);	
				glm::vec3 refractionDirection = glm::normalize(Refract(_ray.GetDirection(), hitNormal, hitInfo.object->GetIor()));
				glm::vec3 refractionColor = GetColor(Ray(hitInfo.intersectPoint, refractionDirection, _ray.GetDepth() + 1));

				pixelColour += refractionColor;
				break;
			}
			default:

				break;
			}
		}
		else
		{
			pixelColour = backgroundColor;
		}
	}
	else
	{
		pixelColour = backgroundColor;
	}

	pixelColour = glm::clamp(pixelColour, 0.0f, 255.0f);
	return pixelColour;
}

HitInfo Scene::SendRay(Ray _ray)
{
	float distance = 2000;
	HitInfo hitInfo;
	hitInfo.hit = false;
	for each (std::shared_ptr<Object> var in objects)
	{
		HitInfo check = var->HasIntersected(_ray);
		if (check.hit && check.distance < distance)
		{
			distance = check.distance;
			hitInfo = check;
		}
	}

	return hitInfo;
}


glm::vec3 Scene::InShadow(HitInfo _info, int _light)
{
	glm::vec3 dir = lights.at(_light)->GetDirection(_info.intersectPoint);
	glm::vec3 origin = _info.intersectPoint + _info.object->Normal(_info.intersectPoint);
	Ray shadowRay = Ray(origin, dir, 0);

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i) != _info.object)
		{
			HitInfo shadow = objects.at(i)->HasIntersected(shadowRay);
			if (shadow.hit)
			{
				return glm::vec3(0);
			}
		}
	}

	return glm::vec3(1);
}

glm::vec3 Scene::Reflect(const glm::vec3 _direction, const glm::vec3 _normal)
{
	return _direction + 2.0f * _normal * -glm::dot(_direction, _normal);
}

glm::vec3 Scene::Refract(const glm::vec3 _direction, const glm::vec3 _normal, const float _ior)
{
	float c1 = glm::dot(_direction, _normal);
	float n1 = 1;
	float n = _ior / n1;

	float c2 = glm::sqrt(1 - glm::pow(n, 2) * (1 - glm::pow(c1, 2)));
	return (n * _direction) + (n * c1 - c2) * _normal;
}

float Scene::Fresnel(const glm::vec3 _direction, const glm::vec3 _normal, const float ior)
{
	float cosi = glm::clamp(glm::dot(_direction, _normal), -1.0f, 1.0f);
	float etai = 1;
	float etat = ior;

	if (cosi > 0)
	{
		std::swap(etai, etat);
	}
	
	float sint = etai / etat * sqrtf(glm::max(0.f, 1 - cosi * cosi));// Compute sini using Snell's law
	// Total internal reflection
	if (sint >= 1)
	{
		return 1;
	}
	else 
	{
		float cost = sqrtf(glm::max(0.f, 1 - sint * sint));
		cosi = fabsf(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		return (Rs * Rs + Rp * Rp) / 2;
	}
	// As a consequence of the conservation of energy, transmittance is given by:
	//kt = 1 - kr;
}
