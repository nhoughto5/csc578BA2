#ifndef LAB01_INCLUDE_SIMPLE_GL_SCENE_HPP
#define LAB01_INCLUDE_SIMPLE_GL_SCENE_HPP

#pragma once

#include <atlas/utils/Scene.hpp>
#include "Swing.hpp"
#include "Structure.hpp"
class LagrangeScene : public atlas::utils::Scene
{
public:
	LagrangeScene();
    ~LagrangeScene();

    void renderScene() override;
	void updateScene(double time) override;
private:
    Swing mSwing;
	Structure mStructure;
};

#endif
