#pragma once
#include <glm.hpp>
#include <core/type.hpp>
#include <list>
#include "Bounding.h"
class BigHouse
{
private:
	glm::vec3 coords;
	glm::mat4 trans = glm::mat4(1.0f);
	std::list<Bounding> Boundaries;

public:
	BigHouse::BigHouse(glm::vec3 coords, float rotation);
	glm::mat4 BigHouse::getTransform();
	std::list<Bounding> BigHouse::getBoundaries();

};

