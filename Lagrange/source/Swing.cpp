#include "Swing.hpp"
#include "ShaderPaths.hpp"
#include <iostream>
#include <atlas/core/Macros.hpp>
USING_ATLAS_GL_NS;
GLushort numIndices, numStringIndices;
Swing::Swing(): 
	width(0.1f), 
	height(0.16f), 
	yLocation(0.5f), 
	stringLength(0.5f),
	massColour{ 1.0f, 0.0f, 0.0f }, 
	pendColour{0.0f, 0.0f, 1.0f},
	x(0.0f),
	thetaDegrees(90.0f),
	thetaRadians(glm::radians(thetaDegrees)),
	pendulumMass(0.2f),
	Mass(0.5f),
	stringColour{0.0f, 1.0f, 0.0f},
	thetaDot(0.0f), thetaDotDot(0.0f),
	xDot(0.0f), xDotDot(0.0f),
	g(-9.81f),
	pendInit(true), stringInit(true)
{
	// Get the path where our shaders are stored.
	std::string shaderDir = generated::ShaderPaths::getShaderDirectory();

	// Now set up the information for our shaders.
	std::vector<ShaderInfo> shaders
	{
		ShaderInfo{ GL_VERTEX_SHADER, shaderDir + "Swing.vs.glsl" },
		ShaderInfo{ GL_FRAGMENT_SHADER, shaderDir + "Swing.fs.glsl" }
	};

	mShaders.push_back(ShaderPointer(new Shader));
	mShaders[0]->compileShaders(shaders);
	mShaders[0]->linkShaders();
	mShaders[0]->disableShaders();
	glGenBuffers(1, &massBuffer);
	glGenBuffers(1, &pendBuffer);
	glGenBuffers(1, &pendIndiciesBuffer);
	glGenBuffers(1, &stringIndiciesBuffer);
	glGenBuffers(1, &stringBuffer);
	defineVAOs();
	sendToOpenGL();
}

Swing::~Swing()
{
    glDeleteVertexArrays(1, &massVao);
	glDeleteVertexArrays(1, &pendVao);
	glDeleteVertexArrays(1, &stringVao);
    glDeleteBuffers(1, &massBuffer);
	glDeleteBuffers(1, &pendBuffer);
	glDeleteBuffers(1, &stringBuffer);
	glDeleteBuffers(1, &pendIndiciesBuffer);
	glDeleteBuffers(1, &stringIndiciesBuffer);
}
void Swing::renderGeometry(atlas::math::Matrix4 projection, atlas::math::Matrix4 view) {
	mShaders[0]->enableShaders();
	glBindVertexArray(massVao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(pendVao);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(stringVao);
	glLineWidth(3.0f);
	glDrawElements(GL_LINES, numStringIndices, GL_UNSIGNED_SHORT, 0);
	glLineWidth(1.0f);
	mShaders[0]->disableShaders();
}
void Swing::updateGeometry(atlas::utils::Time const& t) {
	GLfloat thetaDAMPING = 1.2f, xDAMPING = 1.5f;
	thetaDotDot = ((g*glm::sin(thetaRadians) + thetaDot * xDot * glm::sin(thetaRadians) + xDotDot * glm::cos(thetaRadians)) / stringLength) - thetaDot * thetaDAMPING;
	xDotDot = -(stringLength * pendulumMass * thetaDotDot * glm::cos(thetaRadians)) / (Mass + pendulumMass) - xDot * xDAMPING;

	// ===== Euler Integration==== // Begin
	thetaRadians = thetaRadians + t.deltaTime * thetaDot;
	thetaDot = thetaDot + t.deltaTime * thetaDotDot;
	x = x + t.deltaTime * xDot;
	xDot = xDot + t.deltaTime * xDotDot;
	if (x >= 0.9f-width ) {
		x = 0.9f - 0.2f * width;
		std::cout << "x: " << x << "\n";
	}
	else if (x <= -0.9f + width) {
		x = -0.9f + 0.2f * width;
	}
	else{}
	// ===== Euler Integration==== // End

	thetaDegrees = glm::degrees(thetaRadians);
	sendToOpenGL();
}
void Swing::sendToOpenGL() {
	doMass();
	makePend();
	makeString();
}
void Swing::doMass() {
	glm::vec3 Mass[] = {
		glm::vec3{ width + x, yLocation + height, 0.0f },
		massColour,
		glm::vec3{ width + x, yLocation, 0.0f },
		massColour,
		glm::vec3{ -width + x,yLocation, 0.0f },
		massColour,
		glm::vec3{ width + x, yLocation + height , 0.0f },
		massColour,
		glm::vec3{ -width + x, yLocation , 0.0f },
		massColour,
		glm::vec3{ -width + x, yLocation + height , 0.0f },
		massColour,
	};
	glBindBuffer(GL_ARRAY_BUFFER, massBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Mass), Mass, GL_STATIC_DRAW);

}
void Swing::makePend() {
	ShapeData pendulum = ObjectGenerator::makePendulum(pendColour, thetaRadians, x, yLocation, pendulumMass, stringLength);
	numIndices = pendulum.numIndices;
	glBindBuffer(GL_ARRAY_BUFFER, pendBuffer);
	glBufferData(GL_ARRAY_BUFFER, pendulum.vertexBufferSize(), &pendulum.vertices[0], GL_DYNAMIC_DRAW);
	if (pendInit) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pendIndiciesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLushort), &pendulum.indices[0], GL_DYNAMIC_DRAW);
		pendInit = false;
	}

}
void Swing::makeString() {
	ShapeData string = ObjectGenerator::makeString(stringColour, thetaRadians, x, stringLength, yLocation);
	numStringIndices = string.numIndices;
	glBindBuffer(GL_ARRAY_BUFFER, stringBuffer);
	glBufferData(GL_ARRAY_BUFFER, string.vertexBufferSize(), &string.vertices[0], GL_DYNAMIC_DRAW);
	if (stringInit) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, stringIndiciesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numStringIndices * sizeof(GLushort), &string.indices[0], GL_DYNAMIC_DRAW);
		stringInit = false;
	}

}
void Swing::defineVAOs() {
	glGenVertexArrays(1, &massVao);
	glBindVertexArray(massVao);
	glBindBuffer(GL_ARRAY_BUFFER, massBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &pendVao);
	glBindVertexArray(pendVao);
	glBindBuffer(GL_ARRAY_BUFFER, pendBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pendIndiciesBuffer);

	glGenVertexArrays(1, &stringVao);
	glBindVertexArray(stringVao);
	glBindBuffer(GL_ARRAY_BUFFER, stringBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, stringIndiciesBuffer);
}
