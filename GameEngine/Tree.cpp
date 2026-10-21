#include "Tree.h"
#include <gtx/transform.hpp>


Tree::Tree(glm::vec3 coords) {
	trans = glm::translate(trans, coords);
	trans = glm::scale(trans, glm::vec3(30.0f, 30.0f, 30.0f));
	this->coords = coords;
	this->bound = Bounding::Bounding(5, 5, coords.x, coords.z);
}
glm::mat4 Tree::getTransform() {
	return this->trans;
}
Bounding Tree::getBoundaries() {
	return this->bound;
}
