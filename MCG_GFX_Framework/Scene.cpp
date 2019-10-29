#include "Scene.h"
#include "Camera.h"
#include "Object.h"
#include "Ray.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::DrawScreen(Camera _cam, glm::vec2 _screenSize, std::vector<Object> _objects)
{
	glm::ivec2 pixelPosition;
	glm::ivec3 pixelColour;

	for (size_t x = 0; x < _screenSize.x; x++)
	{
		for (size_t y = 0; y < _screenSize.y; y++)
		{
			pixelPosition = glm::ivec2(x, y);
			Ray ray = cam.GenerateRays(glm::vec2(x, y));

			HitAndPoint check = thing.HasIntersected(ray);
			if (check.hit)
			{
				//std::cout << "Hit!" << std::endl;
				pixelColour = glm::ivec3(255, 0, 0);
			}
			else
			{
				pixelColour = glm::ivec3(0, 0, 0);
			}

			MCG::DrawPixel(pixelPosition, pixelColour);
		}
	}
}
