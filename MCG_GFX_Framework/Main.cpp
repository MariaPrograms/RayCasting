#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>

#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Scene.h"
#include "DistanceLight.h"
#include "PointLight.h"
#include "Light.h"
#include "Plane.h"

#include "MCG_GFX_Lib.h"


int main( int argc, char *argv[] )
{

	//Variable for storing window dimensions
	glm::ivec2 windowSize(1000, 800);

	double duration;
	std::clock_t start;
	
	Scene screen(windowSize);

	Material ground = { glm::fvec3(136, 41, 47), Diffuse };
	Material pink = { glm::fvec3(245.0f, 166.0f, 230.0f), Diffuse };
	Material reflect = { glm::fvec3(162, 126, 168), Refelctive };

	//screen.AddDistantLight(glm::vec3(1), 1.0f, glm::vec3(0, 1, 1.5));
	screen.AddPointLight(glm::vec3(1.0f), 1.0f, glm::vec3(0, 10, -40));

	screen.AddPlane(glm::vec3(0, -11, 0), glm::vec3(0, 1, 0), ground);
	screen.AddSphere(glm::vec3(0, 0, -80), pink, 10);
	screen.AddSphere(glm::vec3(-23, 0, -80), reflect, 10);

	start = std::clock();
	screen.DrawScreen(5, 5);

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Time: " << duration << '\n';
	return MCG::ShowAndHold();
	return 0;
}


