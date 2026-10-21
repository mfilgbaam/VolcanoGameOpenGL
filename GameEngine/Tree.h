
#include <glm.hpp>
#include <core/type.hpp>
#include "Bounding.h"
class Tree
{
private:
	glm::vec3 coords;
	glm::mat4 trans = glm::mat4(1.0f);
	Bounding bound = Bounding::Bounding(0, 0, 0, 0);

public:
	Tree::Tree(glm::vec3 coords);
	glm::mat4 Tree::getTransform();
	Bounding Tree::getBoundaries();
};

