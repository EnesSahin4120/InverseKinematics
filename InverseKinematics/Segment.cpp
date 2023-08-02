#include "Segment.h"

Segment::Segment(GLfloat x, GLfloat y, GLfloat z, GLfloat angle, GLfloat length)
{
	a = glm::vec3(x, y, z);
	this->angle = angle;
	this->length = length;
}

void Segment::Follow(GLfloat x, GLfloat y, GLfloat z) 
{
	glm::vec3 target = glm::vec3(x, y, z);
	glm::vec3 dir = target - a;
	currentDir = glm::normalize(dir);
	a = target - currentDir * length;
}

void Segment::SetupB()
{
	GLfloat dx = length * glm::cos(glm::radians(angle));
	GLfloat dy = length * glm::sin(glm::radians(angle));
	b = glm::vec3(a.x + dx, a.y + dy, 0.0f);
}

void Segment::UpdateB() 
{
	b = glm::vec3(a.x + currentDir.x * length, a.y + currentDir.y * length, a.z + currentDir.z * length);
}

Segment::~Segment()
{
}
