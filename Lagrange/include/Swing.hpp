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
	void updateGeometry(atlas::utils::Time const& t) override;
private:
	void sendToOpenGL();
	void doMass();
	void makePend();
	void makeString();
	void defineVAOs();
	bool stringInit, pendInit;
    GLuint massVao, pendVao, stringVao;
    GLuint massBuffer, stringBuffer, pendBuffer, pendIndiciesBuffer, stringIndiciesBuffer;
	GLfloat x, thetaDegrees, thetaRadians, stringLength;
	GLfloat width, height, yLocation, pendulumMass, Mass, thetaDotDot, xDotDot, thetaDot, xDot, g;
	glm::vec3 massColour, pendColour, stringColour;
};

#endif