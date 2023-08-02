#include "IKController.h"
#include "Segment.h"

IKController::IKController(GLint segmentPairsCount, GLfloat segmentLength, glm::vec3 rootPos)
{
	this->segmentPairsCount = segmentPairsCount;
	this->segmentLength = segmentLength;
	this->rootPos = rootPos;
}

void IKController::SetupLinks()
{
	Segment* current = new Segment(0.0f, 0.0f, 0.0f, 90.0f, segmentLength);
	for (int i = 0;i < segmentPairsCount;i++) 
	{
		Segment* first = current;
		first->SetupB();
		Segment* second = new Segment(first->b.x, first->b.y, first->b.z, 90.0f, segmentLength);
		second->SetupB();
		current = new Segment(second->b.x, second->b.y, second->b.z, 90.0f, segmentLength);

		segments.push_back(first);
		segments.push_back(second);
	}
}

void IKController::RootControl(bool* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_W])
		rootPos.z += deltaTime;

	if (keys[GLFW_KEY_S])
		rootPos.z -= deltaTime;

	if (keys[GLFW_KEY_A])
		rootPos.x += deltaTime;

	if (keys[GLFW_KEY_D])
		rootPos.x -= deltaTime;

	if (keys[GLFW_KEY_UP])
		rootPos.y += deltaTime;

	if (keys[GLFW_KEY_DOWN])
		rootPos.y -= deltaTime;
}

void IKController::UpdateLinks(std::vector<Line*> &lines)
{
	lines.clear();
	for (int i = 0; i < segments.size() - 1; i++) 
	{
		segments[i]->UpdateB();
		segments[i + 1]->a = segments[i]->b;
		segments[i + 1]->UpdateB();
		if (i != segments.size() - 2)
			segments[i + 1]->Follow(segments[i + 2]->a.x, segments[i + 2]->a.y, segments[i + 2]->a.z);
		else
			segments[i + 1]->Follow(rootPos.x, rootPos.y, rootPos.z);

		segments[i]->Follow(segments[i + 1]->a.x, segments[i + 1]->a.y, segments[i + 1]->a.z);

		Line *firstLine = new Line();
		GLfloat firstVertices[] = 
		{
			segments[i]->a.x, segments[i]->a.y, segments[i]->a.z,
			segments[i]->b.x, segments[i]->b.y, segments[i]->b.z
		};
		firstLine->CreateLine(firstVertices, 6);
		lines.push_back(firstLine);

		Line *secondLine = new Line();
		GLfloat secondVertices[] =
		{
			segments[i]->b.x, segments[i]->b.y, segments[i]->b.z,
			segments[i + 1]->b.x, segments[i + 1]->b.y, segments[i + 1]->b.z
		};
		secondLine->CreateLine(secondVertices, 6);
		lines.push_back(secondLine);
	}
}

IKController::~IKController()
{
}
