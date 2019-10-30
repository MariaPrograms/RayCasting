
#include <cmath>
#include <iostream>
#include<vector>

#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Scene.h"
#include "MCG_GFX_Lib.h"


int main( int argc, char *argv[] )
{
	// Variable for storing window dimensions
	glm::ivec2 windowSize( 800, 600 );

	Scene screen(windowSize);
	Camera cam(windowSize);
	std::vector<std::shared_ptr<Object>> objects;

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(0, 0, -75), glm::ivec3(1, 1, 1), 10);
	objects.push_back(sphere);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(-10, -7, -40), glm::vec3(0, 1, 1), 5);
	objects.push_back(sphere1);

	screen.DrawScreen(cam, objects);

	/*glm::ivec2 pixelPosition;
	glm::ivec3 pixelColour;

	for (size_t x = 0; x < windowSize.x; x++)
	{
		for (size_t y = 0; y < windowSize.y; y++)
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
	}*/
	
	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	return MCG::ShowAndHold();
	return 0;
	

}


