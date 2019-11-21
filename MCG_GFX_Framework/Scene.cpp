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

void Scene::DrawScreenPart(glm::vec2 _startPos, glm::vec2 _endPos)
{
	glm::ivec2 pixelPosition;
	glm::ivec3 pixelColour;

	for (int x = _startPos.x; x < _endPos.x; x++)
	{
		for (int y = _startPos.y; y < _endPos.y; y++)
		{
			float distance = 2000;
			pixelPosition = glm::ivec2(x, y);
			Ray ray = camera->GenerateRays(glm::vec2(x, y));
			pixelColour = glm::ivec3(50, 50, 70);

			for each (std::shared_ptr<Object> var in objects)
			{
				HitAndPoint check = var->HasIntersected(ray);
				if (check.hit && check.distance < distance)
				{
					if (!InShadow(check.intersectPoint, var))
					{
						distance = check.distance;
						pixelColour = var->LightShade(ray, check.intersectPoint, lights.at(0));
					}
				}
			}

			MCG::DrawPixel(pixelPosition, pixelColour);
		}
	}
}

bool Scene::InShadow(glm::vec3 _intersectPoint, std::shared_ptr<Object> _object)
{
	Ray shadowRay = camera->ShadowRay(_intersectPoint, lights.at(0)->GetDirection(_intersectPoint));
	
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i) != _object)
		{
			HitAndPoint shadow = objects.at(i)->HasIntersected(shadowRay);
			if (shadow.hit)
			{
				return true;
			}
		}
	}

	return false;
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