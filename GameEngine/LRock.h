#include <glm.hpp>
#include <core/type.hpp>
#include "Bounding.h"
class LRock
{
private:
	glm::vec3 coords;
	glm::mat4 trans = glm::mat4(1.0f);
	Bounding bound = Bounding::Bounding(0, 0, 0, 0);
	bool check = false;

public:
	LRock::LRock(glm::vec3 coords);
	glm::mat4 LRock::getTransform();
	Bounding LRock::getBoundaries();
	bool LRock::Fall(float DeltaTime);
};

