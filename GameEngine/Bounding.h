#pragma once
#include <glm.hpp>
#include <core/type.hpp>
class Bounding
{
private:
	float x, z, centerx, centerz;

public:
	Bounding(float x, float z, float centerx, float centerz);
	Bounding::Bounding() { Bounding bound = Bounding::Bounding(0, 0, 0, 0); }
	bool Collide(glm::vec3 pos);

};

