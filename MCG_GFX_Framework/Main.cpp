
#include <cmath>
#include <iostream>
#include <vector>
#include <thread>

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
	std::vector<std::shared_ptr<Object>> objects;

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(0, 0, -75), glm::ivec3(1, 0, 1), 10);
	objects.push_back(sphere);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(-5, -1, -80), glm::vec3(0, 1, 1), 10);
	objects.push_back(sphere1);

	//std::thread t(&Scene::DrawScreen, &screen, objects, 2, 2);
	screen.DrawScreen(objects, 2, 2);

	
	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	return MCG::ShowAndHold();
	return 0;
	

}


