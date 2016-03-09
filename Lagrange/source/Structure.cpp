#include "Structure.hpp"
#include "ShaderPaths.hpp"
#include <atlas/core/Macros.hpp>
Structure::Structure() {
	USING_ATLAS_GL_NS;

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);
	GLfloat height = 0.5f, width = 0.9f, verticalHeight = 0.1f;
	GLfloat vertices[6][2] = {
		//Horizontal bar
		{ -width, height },
		{ width, height},

		//Left Vertical
		{ -width, height + verticalHeight },
		{ -width, height - verticalHeight},

		//Right Vertical
		{ width, height + verticalHeight },
		{ width, height - verticalHeight },
	};

	glGenBuffers(1, &mBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Get the path where our shaders are stored.
	std::string shaderDir = generated::ShaderPaths::getShaderDirectory();

	// Now set up the information for our shaders.
	std::vector<ShaderInfo> shaders
	{
		ShaderInfo{ GL_VERTEX_SHADER, shaderDir + "structure.vs.glsl" },
		ShaderInfo{ GL_FRAGMENT_SHADER, shaderDir + "structure.fs.glsl" }
	};

	// Create a new shader and add it to our list.
	mShaders.push_back(ShaderPointer(new Shader));

	// Compile the shaders.
	mShaders[0]->compileShaders(shaders);

	// And link them.
	mShaders[0]->linkShaders();

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Disable at the end to avoid mixing shaders.
	mShaders[0]->disableShaders();

}
Structure::Structure(GLuint sceneWidth_, GLuint sceneHeight_) : sceneHeight(sceneHeight_), sceneWidth(sceneWidth_){

}
Structure::~Structure() {

}

void Structure::renderGeometry(atlas::math::Matrix4 projection,	atlas::math::Matrix4 view) {
	// To avoid warnings from unused variables, you can use the 
	// UNUSED macro.
	UNUSED(projection);
	UNUSED(view);

	// Enable the shaders.
	mShaders[0]->enableShaders();

	glBindVertexArray(mVao);
	glLineWidth(2.0f);
	glDrawArrays(GL_LINES, 0, 6);
	glLineWidth(1.0f);
	// Disable them.
	mShaders[0]->disableShaders();
}