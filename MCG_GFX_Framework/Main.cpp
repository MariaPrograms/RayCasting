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


int main(int argc, char *argv[])
{

	//Variable for storing window dimensions
	glm::ivec2 windowSize(1000, 800);

	double duration;
	std::clock_t start;

	Scene screen(windowSize);

	Material reflect = { glm::fvec3(255, 250, 250), Refelctive };
	Material ground = { glm::fvec3(136, 41, 47), Diffuse };

	Material cream = { glm::fvec3(255.0f, 237.0f, 237.0f), Diffuse };
	Material pink = { glm::fvec3(245.0f, 166.0f, 230.0f), Diffuse };
	Material purple = { glm::fvec3(204, 153, 255), Diffuse };
	Material lime = { glm::fvec3(178, 255, 102), Diffuse };
	Material lightBlue = { glm::fvec3(102, 255, 255), Diffuse };
	Material black = { glm::fvec3(128), Diffuse };

	/*
	//SnowMan
	screen.SetBackgroundColor(glm::vec3(2, 184, 212));
	screen.AddDistantLight(glm::vec3(1), 1.0f, glm::vec3(0, 1, 1));

	screen.AddPlane(glm::vec3(0, -10, 0), glm::vec3(0, 1, 0), ground); //Ground

	screen.AddSphere(glm::vec3(2, 20, -74), black, .5); //Eye
	screen.AddSphere(glm::vec3(-2, 20, -74), black, .5); //Eye
	screen.AddSphere(glm::vec3(0, 20, -78), cream, 4.5); //Head

	screen.AddSphere(glm::vec3(0, 11, -79), cream, 6); //Body
	screen.AddSphere(glm::vec3(0, 11, -73.5), black, 1); //Button
	screen.AddSphere(glm::vec3(0, 14, -74), black, 1); //Button
	screen.AddSphere(glm::vec3(0, 8, -74), black, 1); //Button

	screen.AddSphere(glm::vec3(0, -2, -80), cream, 9); //Bottom
	*/

	/*
	//Shadows on plane
	Material brown = { glm::fvec3(144, 87, 82), Diffuse };
	Material pinky = { glm::fvec3(180, 134, 159), Diffuse };
	Material violet = { glm::fvec3(207, 200, 230), Diffuse };
	Material marroon = { glm::fvec3(110, 69, 85), Diffuse };

	screen.SetBackgroundColor(glm::vec3(166, 177, 225));
	screen.AddDistantLight(glm::vec3(1), 1.0f, glm::vec3(0, 1, .2));

	screen.AddPlane(glm::vec3(0, -10, 0), glm::vec3(0, 1, 0), reflect); //Ground

	screen.AddSphere(glm::vec3(0, 0, -70), violet, 10); //Centre
	screen.AddSphere(glm::vec3(-25, 0, -95), pinky, 10); //Left
	screen.AddSphere(glm::vec3(25, 0, -95), marroon, 10); //Right
	*/

	
	/*
	//Shadows on circles
	screen.SetBackgroundColor(glm::vec3(204, 229, 255));
	screen.AddPointLight(glm::vec3(1), 1.0f, glm::vec3(-20, 20, -70));

	screen.AddPlane(glm::vec3(0, -10, 0), glm::vec3(0, 1, 0), ground); //Ground
	screen.AddSphere(glm::vec3(-5, 0, -80), lime, 10); //Centre
	screen.AddSphere(glm::vec3(-17, 15, -75), purple, 5); //Left
	screen.AddSphere(glm::vec3(19, 5, -80), pink, 15); //Right
	*/

	/*
	//Reflections on plane
	Material pinky = { glm::fvec3(180, 134, 159), Diffuse };
	Material violet = { glm::fvec3(207, 200, 230), Diffuse };
	Material marroon = { glm::fvec3(110, 69, 85), Diffuse };

	screen.SetBackgroundColor(glm::vec3(166, 177, 225));
	screen.AddDistantLight(glm::vec3(1), 1.0f, glm::vec3(0, 1, 1));

	screen.AddPlane(glm::vec3(0, -10, 0), glm::vec3(0, 1, 0), reflect); //Ground

	screen.AddSphere(glm::vec3(0, 0, -70), violet, 10); //Centre
	screen.AddSphere(glm::vec3(-25, 0, -95), pinky, 10); //Left
	screen.AddSphere(glm::vec3(25, 0, -95), marroon, 10); //Right
	*/


	//Shadows on circles
	screen.SetBackgroundColor(glm::vec3(204, 229, 255));
	screen.AddDistantLight(glm::vec3(1), 1.0f, glm::vec3(0, 1, 1));

	screen.AddPlane(glm::vec3(0, -10, 0), glm::vec3(0, 1, 0), ground); //Ground
	screen.AddSphere(glm::vec3(25, 0, -80), lime, 10); //Right

	screen.AddSphere(glm::vec3(-25, 10, -75), purple, 5); //Left Top
	screen.AddSphere(glm::vec3(-25, -5, -75), reflect, 5); //Left Top

	screen.AddSphere(glm::vec3(-2, 5, -80), reflect, 15); //Centre



	start = std::clock();
	screen.DrawScreen(3, 3);

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Time: " << duration << '\n';
	return MCG::ShowAndHold();
	return 0;
}


