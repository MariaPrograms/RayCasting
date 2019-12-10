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
	Material reflect = { glm::fvec3(255, 250, 250), Refelctive };
	Material snow = { glm::fvec3(255.0f, 237.0f, 237.0f), Diffuse };
	Material black = { glm::fvec3(128), Diffuse };

	/*
	screen.SetBackgroundColor(glm::vec3(2, 184, 212));
	screen.AddDistantLight(glm::vec3(1), 1.0f, glm::vec3(0, 1, 1));

	screen.AddPlane(glm::vec3(0, -10, 0), glm::vec3(0, 1, 0), ground); //Ground

	screen.AddSphere(glm::vec3(2, 20, -74), black, .5); //Eye
	screen.AddSphere(glm::vec3(-2, 20, -74), black, .5); //Eye
	screen.AddSphere(glm::vec3(0, 20, -78), snow, 4.5); //Head

	screen.AddSphere(glm::vec3(0, 11, -79), snow, 6); //Body
	screen.AddSphere(glm::vec3(0, 11, -73.5), black, 1); //Button
	screen.AddSphere(glm::vec3(0, 14, -74), black, 1); //Button
	screen.AddSphere(glm::vec3(0, 8, -74), black, 1); //Button

	screen.AddSphere(glm::vec3(0, -2, -80), snow, 9); //Bottom
	*/

	screen.SetBackgroundColor(glm::vec3(200));
	screen.AddPointLight(glm::vec3(1.0f), 1.0f, glm::vec3(0, 30, -40));

	screen.AddPlane(glm::vec3(0, -10, 0), glm::vec3(0, 1, 0), ground); //Ground
	screen.AddSphere(glm::vec3(0, 0, -50), pink, 10); //Bottom


	start = std::clock();
	screen.DrawScreen(3, 3);

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Time: " << duration << '\n';
	return MCG::ShowAndHold();
	return 0;
}


