
#include <cmath>
#include <iostream>
#include<vector>

#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "MCG_GFX_Lib.h"


int main( int argc, char *argv[] )
{
	// Variable for storing window dimensions
	glm::ivec2 windowSize( 800, 600 );

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if(!MCG::Init( windowSize ))
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground(glm::ivec3(0,0,0));

	Camera cam(windowSize);
	glm::ivec2 pixelPosition;
	glm::ivec3 pixelColour;
	Sphere thing = Sphere(glm::vec3(0, 0, -50), glm::vec3(0, 1, 1), 10);

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
	}
	
	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	return MCG::ShowAndHold();
	return 0;
	

}


