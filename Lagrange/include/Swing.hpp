#ifndef LAB01_INCLUDE_SIMPLE_GL_TRIANGLE_HPP
#define LAB01_INCLUDE_SIMPLE_GL_TRIANGLE_HPP

#pragma once
#include "ShapeData.h"
#include "ObjectGenerator.h"
#include <atlas/utils/Geometry.hpp>

class Swing : public atlas::utils::Geometry
{
public:
    Swing();
    ~Swing();

    void renderGeometry(atlas::math::Matrix4 projection, atlas::math::Matrix4 view) override;

private:
	void sendToOpenGL();
	void doMass();
	void makePend();
	void makeString();
	void defineVAOs();
    GLuint massVao, pendVao, stringVao;
    GLuint massBuffer, stringBuffer, pendBuffer, pendIndiciesBuffer, stringIndiciesBuffer;
	GLfloat x, theta, stringLength;
	GLfloat width, height, yLocation, pendulumMass, mass;
	glm::vec3 massColour, pendColour, stringColour;
};

#endif