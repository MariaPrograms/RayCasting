#include "MCG_GFX_Lib.h"
#include <iostream>

#include "Scene.h"
#include "Camera.h"
#include "Object.h"
#include "Ray.h"


Scene::Scene(glm::ivec2 _windowSize)
{
	windowSize = _windowSize;

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

void Scene::DrawScreen(Camera _cam, std::vector<std::shared_ptr<Object>> _objects)
{
	glm::ivec2 pixelPosition;
	glm::ivec3 pixelColour;

	for (size_t x = 0; x < windowSize.x; x++)
	{
		for (size_t y = 0; y < windowSize.y; y++)
		{
			glm::vec3 distance = glm::vec3(0, 0, 0);
			pixelPosition = glm::ivec2(x, y);
			Ray ray = _cam.GenerateRays(glm::vec2(x, y));
			std::shared_ptr<Object> obj;

			for each (std::shared_ptr<Object> var in _objects)
			{
				HitAndPoint check = var->HasIntersected(ray);
				if (check.hit)
				{
					//std::cout << glm::greaterThan(distance, check.distance).b << std::endl;
					obj = var;
				}
			}
			
			if (obj)
			{
				pixelColour = obj->GetColor();
			}
			else
			{
				pixelColour = glm::ivec3(0, 0, 0);
			}

			MCG::DrawPixel(pixelPosition, pixelColour);
		}
	}
}
