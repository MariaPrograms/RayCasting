#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>

#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Scene.h"
#include "MCG_GFX_Lib.h"


int main( int argc, char *argv[] )
{
	//Variable for storing window dimensions
	glm::ivec2 windowSize( 800, 600 );

	double duration;
	std::clock_t start;
	
	Scene screen(windowSize);
	std::vector<std::shared_ptr<Object>> objects;

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(0.5, 0.5, -80), glm::fvec3(.24, .5, 1), 10);
	objects.push_back(sphere);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(-5, -1, -69), glm::vec3(1, 0, 1), 10);
	objects.push_back(sphere1);

	start = std::clock();
	screen.DrawScreen(objects, 2, 2);

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Time: " << duration << '\n';
	return MCG::ShowAndHold();
	return 0;
}


