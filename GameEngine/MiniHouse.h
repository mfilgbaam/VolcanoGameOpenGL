#pragma once
#include <glm.hpp>
#include <core/type.hpp>
#include <list>
#include "Bounding.h"
class MiniHouse
{
private:
	glm::vec3 coords;
	glm::mat4 trans = glm::mat4(1.0f);
	std::list<Bounding> Boundaries;

public:
	MiniHouse::MiniHouse(glm::vec3 coords, float rotation);
	glm::mat4 MiniHouse::getTransform();
	std::list<Bounding> MiniHouse::getBoundaries();

};

