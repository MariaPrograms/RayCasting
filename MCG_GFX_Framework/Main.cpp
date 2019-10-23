
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
	glm::ivec2 windowSize( 640, 480 );

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !MCG::Init( windowSize ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	MCG::SetBackground( glm::ivec3(0,0,0) );

	// Preparing a position to draw a pixel


	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 255
	


	// Draws a single pixel at the specified coordinates in the specified colour!
	//

	// Do any other DrawPixel calls here
	// ...

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	//return MCG::ShowAndHold();

	Camera cam(windowSize);
	std::vector<Ray> screenRays;
	Sphere thing = Sphere(glm::vec3(windowSize.x/2, windowSize.y / 2, 21), glm::vec3(0, 1, 1), 20);

	for (size_t x = 0; x < windowSize.x; x++)
	{
		for (size_t y = 0; y < windowSize.y; y++)
		{
			screenRays.push_back(cam.GenerateRays(glm::vec2(x, y)));
		}
	}

	glm::ivec2 pixelPosition;
	glm::ivec3 pixelColour;

	for each (Ray var in screenRays)
	{
		pixelPosition = glm::ivec2(var.GetOrgin().x, var.GetOrgin().y);

		HitAndPoint check = thing.HasIntersected(var);
		if (check.hit)
		{
			std::cout << "Hit! at (" << check.distance.x << ", " << check.distance.y << ", " << check.distance.z << ")" << std::endl;
			pixelColour = glm::ivec3(255, 0, 0);
		}
		else
		{
			pixelColour = glm::ivec3(0, 0, 0);
		}
		MCG::DrawPixel(pixelPosition, pixelColour);
	}
	
	// Variable to keep track of time
	float timer = 0.0f;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while( MCG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		/*MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

		// Change our pixel's X coordinate according to time
		pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		timer += 1.0f / 60.0f;

		// Draw the pixel to the screen
		MCG::DrawPixel( pixelPosition, pixelColour );*/

	}

	return 0;
	

}


