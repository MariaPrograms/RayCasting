#include "MCG_GFX_Lib.h"
#include <iostream>
#include <thread>

#include "Scene.h"
#include "Camera.h"
#include "Object.h"
#include "Ray.h"
#include "Light.h"

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
}

Scene::~Scene()
{

}


/*
Tasks and workers -> hint 
*/
void Scene::DrawScreen(std::vector<std::shared_ptr<Object>> _objects, std::vector<std::shared_ptr<Light>> _lights, int _screenSplitX, int _screenSplitY)
{
	objects = _objects;
	lights = _lights;
	std::vector<std::thread> threads;

	int widthToCheck = windowSize.x / _screenSplitX;
	int hightToCheck = windowSize.y / _screenSplitY;

	for (int x = 0; x < _screenSplitX; x++)
	{
		for (int y = 0; y < _screenSplitY; y++)
		{
			glm::vec2 startpos(widthToCheck * x, hightToCheck * y);
			glm::vec2 endpos(widthToCheck * (x + 1), hightToCheck * (y + 1));

			std::thread t(&Scene::DrawScreenPart, this, startpos, endpos);
			threads.push_back(std::move(t));
		}
	}

	for (auto& t : threads)
	{
		t.join();
	}
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
	glm::vec3 pixelColour = glm::vec3(0);
	if (_ray.GetDepth() < 3)
	{

		HitInfo hitInfo = CheckRay(_ray);

		if (hitInfo.hit)
		{
			switch (hitInfo.object->GetMaterial())
			{
			case Basic:
				pixelColour = hitInfo.object->Shade(_ray, hitInfo.intersectPoint);
				break;

			case Diffuse:
				for (int i = 0; i < lights.size(); i++)
				{
					pixelColour += hitInfo.object->DiffuseShade(_ray, hitInfo.intersectPoint, lights.at(i)) * glm::vec3(InShadow(hitInfo));
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
				glm::vec3 refractDirection = Refract(_ray.GetDirection(), hitNormal, 1.3f);
				Ray reflectRay = Ray(hitInfo.intersectPoint + hitNormal, refractDirection, _ray.GetDepth() + 1);
				
				glm::vec3 refractionColor(0);

				// compute fresnel
				float kr = Fresnel(_ray.GetDirection(), hitNormal, hitInfo.object->GetIor());
				bool outside = glm::dot(_ray.GetDirection(), hitNormal) < 0;

				// compute refraction if it is not a case of total internal reflection
				if (kr < 1) 
				{
					glm::vec3 refractionDirection = glm::normalize(Refract(_ray.GetDirection(), hitNormal, hitInfo.object->GetIor()));
					refractionColor = GetColor(Ray(hitInfo.intersectPoint, refractionDirection, _ray.GetDepth() + 1));
				}

				glm::vec3 reflectionDirection = glm::normalize(Reflect(_ray.GetDirection(), hitNormal));
				glm::vec3 reflectionColor = GetColor(Ray(hitInfo.intersectPoint, reflectionDirection, _ray.GetDepth() + 1));

				// mix the two
				pixelColour += reflectionColor * kr + refractionColor * (1 - kr);
				break;
			}
			default:

				break;
			}
		}
		else
		{
			pixelColour = glm::vec3(184, 74, 98);
		}
	}

	pixelColour = glm::clamp(pixelColour, glm::vec3(0), glm::vec3(255));
	return pixelColour;
}

int Scene::InShadow(HitInfo _info)
{
	glm::vec3 dir = lights.at(0)->GetDirection(_info.intersectPoint);
	glm::vec3 origin = _info.intersectPoint + _info.object->Normal(_info.intersectPoint);
	Ray shadowRay = Ray(origin, dir, 0);

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i) != _info.object)
		{
			HitInfo shadow = objects.at(i)->HasIntersected(shadowRay);
			if (shadow.hit)
			{
				return 0;
			}
		}
	}

	return 1;
}

glm::vec3 Scene::Reflect(const glm::vec3 _direction, const glm::vec3 _normal)
{
	return _direction - 2.0f * _normal * glm::dot(_direction, _normal);
}

glm::vec3 Scene::Refract(const glm::vec3 _direction, const glm::vec3 _normal, const float _ior)
{
	float cosi = glm::clamp(glm::dot(_direction, _normal), -1.0f, 1.0f);
	float etai = 1;
	float etat = _ior;
	glm::vec3 n = _normal;

	if (cosi < 0)
	{
		cosi = -cosi;
	}
	else
	{
		std::swap(etai, etat); 
		n = -_normal;
	}

	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi);

	return k < 0 ? glm::vec3(0) : eta * _direction + (eta * cosi - sqrtf(k)) * n;
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

HitInfo Scene::CheckRay(Ray _ray)
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

