#include "ObjectGenerator.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a); //Used to dynamically caculate the number of elements in an array

ShapeData ObjectGenerator::makePendulum(glm::vec3 colour, GLfloat angle, GLfloat x, GLfloat y, GLfloat mass, GLfloat stringLength) {
	angle = glm::radians(-angle);
	ShapeData ret;
	GLfloat radius = 0.1 * mass;
	glm::vec3 centerOfBall = glm::vec3{x, y - stringLength - radius, 0.0f};
	glm::vec3 anchorPosition = glm::vec3{ x,y,0.0f };
	std::vector<glm::vec3> vertices;
	std::vector<GLushort> indices;
	GLuint count = 1;
	glm::vec3 old;
	vertices.push_back(glm::vec3{ getRotatedX(angle, centerOfBall, anchorPosition), getRotatedY(angle, centerOfBall, anchorPosition), 0.0f });
	vertices.push_back(colour);
	for (double i = 0; i < 2 * M_PI; i += M_PI / 24) {
		old = glm::vec3{ (std::cos(i) * radius) + centerOfBall.x, (std::sin(i) * radius) + centerOfBall.y, 0.0f };
		//vertices.push_back(old);
		vertices.push_back(glm::vec3(getRotatedX(angle, old, anchorPosition),getRotatedY(angle, old, anchorPosition),0.0f));
		vertices.push_back(colour);
		++count;
	}

	indices.push_back(0);
	for (int i = 2; i < count; ++i) {
		indices.push_back(i);
		indices.push_back(i+1);
		indices.push_back(1);
	}
	indices.push_back(count);
	indices.push_back(1);
	indices.push_back(0);

	ret.numVertices = vertices.size();
	ret.vertices = vertices;
	ret.indices = indices;
	ret.numIndices = indices.size();
	return ret;
}
ShapeData ObjectGenerator::makeString(glm::vec3 colour, GLfloat angle, GLfloat x, GLfloat stringLength, GLfloat y) {
	ShapeData ret;
	angle = glm::radians(-angle);
	std::vector<glm::vec3> vertices;
	glm::vec3 anchorPosition = glm::vec3{ x,y,0.0f };
	glm::vec3 connectionPoint = glm::vec3{x, y - stringLength, 0.0f};
	connectionPoint = glm::vec3{ getRotatedX(angle, connectionPoint, anchorPosition), getRotatedY(angle, connectionPoint, anchorPosition), 0.0f };
	vertices.push_back(anchorPosition);
	vertices.push_back(colour);
	vertices.push_back(connectionPoint);
	vertices.push_back(colour);
	std::vector<GLushort> indices;
	indices.push_back(0);
	indices.push_back(1);
	ret.numVertices = vertices.size();
	ret.vertices = vertices;
	ret.indices = indices;
	ret.numIndices = indices.size();
	return ret;
}
//Compute the new rotated X position of the vertices around anchorPosisition
GLfloat ObjectGenerator::getRotatedX(GLfloat angle, glm::vec3 old, glm::vec3 anchorPosition) {
	GLfloat ret = (glm::cos(angle) * (old.x - anchorPosition.x)) + (glm::sin(angle) * (old.y - anchorPosition.y)) + anchorPosition.x;
	return ret;
}
//Compute the new rotated Y position of the vertices around anchorPosisition
GLfloat ObjectGenerator::getRotatedY(GLfloat angle, glm::vec3 old, glm::vec3 anchorPosition) {
	GLfloat ret = -(glm::sin(angle) * (old.x - anchorPosition.x)) + (glm::cos(angle) * (old.y - anchorPosition.y)) + anchorPosition.y;
	return ret;
}