#include "LagrangeScene.hpp"

LagrangeScene::LagrangeScene()
{
    // Initialize the matrices to identities.
    mProjection = atlas::math::Matrix4(1.0f);
    mView = atlas::math::Matrix4(1.0f);
}

LagrangeScene::~LagrangeScene()
{ }

void LagrangeScene::renderScene()
{
	float grey = 200.0f / 255.0f;
	glClearColor(grey, grey, grey, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	mStructure.renderGeometry(mProjection, mView);
	mSwing.renderGeometry(mProjection, mView);
}
void LagrangeScene::updateScene(double time) {

}