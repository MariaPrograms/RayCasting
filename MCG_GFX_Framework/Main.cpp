#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>

#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Scene.h"
#include "DistanceLight.h"
#include "PointLight.h"
#include "Light.h"

#include "MCG_GFX_Lib.h"


int main( int argc, char *argv[] )
{
	//Variable for storing window dimensions
	glm::ivec2 windowSize( 800, 600 );

	double duration;
	std::clock_t start;
	
	Scene screen(windowSize);
	std::vector<std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<Light>> lights;

	std::shared_ptr<DistanceLight> dLight = std::make_shared<DistanceLight>(glm::vec3(1), 1.0f, glm::vec3(0, 1, 0));
	std::shared_ptr<DistanceLight> dLight1 = std::make_shared<DistanceLight>(glm::vec3(1), 1.0f, glm::vec3(0, -1, 0));
	std::shared_ptr<PointLight> pLight = std::make_shared<PointLight>(glm::vec3(1.0f), 1.0f, glm::vec3(20, -30, -80));
	
	lights.push_back(dLight);
	//lights.push_back(pLight);
	lights.push_back(dLight1);

	std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(21, 0, -80), glm::fvec3(245.0f /255.0f, 166.0f /255.0f, 230.0f /255.0f), Diffuse, "Blue" , 10);
	sphere->self = sphere;
	objects.push_back(sphere);

	std::shared_ptr<Sphere> sphere1 = std::make_shared<Sphere>(glm::vec3(-21, 0, -80), glm::fvec3(84.0f/255.0f, 69.0f /255.0f, 127.0f /255.0f), Diffuse, "Purple", 10);
	sphere1->self = sphere1;
	objects.push_back(sphere1);

	std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(glm::vec3(0, 0, -80), glm::fvec3(172/255.0f, 123/255.0f, 132/255.0f), Refelctive, "Ground" , 10);
	sphere2->self = sphere2;
	objects.push_back(sphere2);

	start = std::clock();
	screen.DrawScreen(objects, lights, 2, 4);

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Time: " << duration << '\n';
	return MCG::ShowAndHold();
	return 0;
}


