#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP
#pragma once
#include <atlas/utils/Geometry.hpp>
class Structure : public atlas::utils::Geometry {
public:
	Structure();
	Structure(GLuint sceneWidth_, GLuint sceneHeight_);
	~Structure();

	void renderGeometry(atlas::math::Matrix4 projection, atlas::math::Matrix4 view) override;

private:
	GLuint sceneWidth, sceneHeight, mVao, mBuffer;
};
#endif // !STRUCTURE_HPP
