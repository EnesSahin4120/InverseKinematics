#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Segment
{
public:
	Segment(GLfloat x, GLfloat y, GLfloat z, GLfloat angle, GLfloat length);
	
	glm::vec3 a;
	glm::vec3 b;

	void Follow(GLfloat x, GLfloat y, GLfloat z);
	void SetupB();
	void UpdateB();

	~Segment();
private:
	GLfloat angle;
	GLfloat length;
	glm::vec3 currentDir;
};

