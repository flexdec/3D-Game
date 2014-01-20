#include "tp1.h"
#include <iostream>

CoreTP1::CoreTP1() : Core(),
b(vec3(1.0, 0.5, 1), vec3(1, 0, 0)),
b2(vec3(0.3, 0.3, 0.3), vec3(0,0,1)),
plane(vec3(4,0.1f,4), vec3(0,1,0)), 
f(0)
{
	/******* BABY MAKING ******/
	b.AddChild(b2);

	/******* STATIC MATRIX DEFINITIONS ******/

	//VIEW MATRIX
	_viewMatrix = glm::lookAt(glm::vec3(0, 1, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	//SHEAR MATRIX
	float shear[16] = {
		1, 0, 0, 0,
		-0.2, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	float shearInverted[16] = {
		1, 0, 0, 0,
		0.2, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	shear_matrix = glm::make_mat4(shear);
	shear_matrix_inv = glm::make_mat4(shearInverted);

	//FLOOR TRANSLATION MATRIX
	b2_set_pos = (glm::translate(glm::mat4(), glm::vec3(0, 0.4, 0)));
	

	
	
}

void CoreTP1::Render(double dt) //dt is the time unit
{

	/******* DYNAMIC MATRIX DEFINITIONS ******/
	glm::mat4 rotating_matrix = glm::rotate(glm::mat4(), f, glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)));
	
	/******* TRANSFORMATIONS SETTING ******/
	
	b.SetTransform(shear_matrix * rotating_matrix);
	b2.SetTransform(b2_set_pos*shear_matrix_inv);
	plane.SetTransform(glm::translate(glm::mat4(), glm::vec3(0, -0.8, 0)));

	/******* RENDERING ******/
	b.Render();
	b2.Render();
	plane.Render();

	/******* UPDATING ******/
	f += (float)dt * 2 * glm::pi<float>() * 0.1f;
}

CoreTP1::~CoreTP1()
{
}	
