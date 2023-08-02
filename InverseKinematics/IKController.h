#pragma once

#include <vector>
#include "Segment.h"
#include "Line.h"

#include <GLFW\glfw3.h>

class IKController
{
public:
	IKController(GLint segmentPairsCount, GLfloat segmentLength, glm::vec3 rootPos);

	void SetupLinks();
	void UpdateLinks(std::vector<Line*> &lines);
	void RootControl(bool* keys, GLfloat deltaTime);

	~IKController();
private:
	glm::vec3 rootPos;

	GLint segmentPairsCount;
	std::vector<Segment*> segments;
	GLfloat segmentLength;
};

