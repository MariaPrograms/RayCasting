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
			Ray reflectRay = camera->SpecificRay(hitInfo.intersectPoint + hitNormal, reflectedDirection);
			pixelColour += glm::vec3(0.8) * GetColor(reflectRay);
			break;
		}
		case Refraction:

			break;
		default:

			break;

		}
	}
	else
	{
		pixelColour = glm::vec3(184, 74, 98);
	}

	
	pixelColour = glm::clamp(pixelColour, glm::vec3(0), glm::vec3(255));
	return pixelColour;
}

int Scene::InShadow(HitInfo _info)
{
	glm::vec3 dir = lights.at(0)->GetDirection(_info.intersectPoint);
	glm::vec3 org = _info.intersectPoint + _info.object->Normal(_info.intersectPoint);
	Ray shadowRay = camera->SpecificRay(org, dir);

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i) != _info.object)
		{
			HitInfo shadow = objects.at(i)->HasIntersected(shadowRay);
			if (shadow.hit)
			{
				std::cout << _info.object->name << " hit " << objects.at(i)->name << std::endl;
				return 0;
			}
		}
	}

	return 1;
}


glm::vec3 Scene::Reflect(const glm::vec3 &_direction, const glm::vec3 &_normal)
{
	return _direction - 2 * glm::dot(_direction, _normal) * _normal;
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
			for (int i = 0; i < lights.size(); i++)
			{
				distance = check.distance;
				hitInfo = check;
			}
		}
	}

	return hitInfo;
}

