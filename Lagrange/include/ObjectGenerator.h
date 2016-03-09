#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H
#pragma once
#include <atlas/utils/Geometry.hpp>
#include "ShapeData.h"
#include "Vertex.h"
class ObjectGenerator {
public:
	static ShapeData makePendulum(glm::vec3 colour, GLfloat angle, GLfloat x, GLfloat y, GLfloat mass, GLfloat stringLength);
	static ShapeData makeString(glm::vec3 colour, GLfloat angle, GLfloat x, GLfloat stringLength, GLfloat y);
private:
	static GLfloat getRotatedX(GLfloat angle, glm::vec3 old, glm::vec3 anchorPosition);
	static GLfloat getRotatedY(GLfloat angle, glm::vec3 old, glm::vec3 anchorPosition);
};
#endif // !SHAPEGENERATOR_H