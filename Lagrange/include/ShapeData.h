#ifndef SHAPE_DATA_H
#define SHAPE_DATA_H
#pragma once
#include <atlas/utils/Geometry.hpp>

#include "Vertex.h"

struct ShapeData {
	ShapeData() : vertices(0), numVertices(0), indices(0), numIndices(0) {};
	std::vector<glm::vec3> vertices;
	GLuint numVertices;
	std::vector<GLushort> indices;
	GLuint numIndices;
	glm::vec3 connectionPoint;
	glm::vec3 getConnectionPoint() {
		return connectionPoint;
	}
	GLsizeiptr vertexBufferSize() const {
		GLsizeiptr ret = numVertices * 6 * sizeof(float);
		return ret;
	}
	GLsizeiptr indexBufferSize() const {
		return numIndices * sizeof(GLushort);
	}
	void cleanup() {
		vertices.clear();
		indices.clear();
		numIndices = numVertices = 0;
	}
};
#endif