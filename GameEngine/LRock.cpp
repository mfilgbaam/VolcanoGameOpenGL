#include "LRock.h"
#include <gtx/transform.hpp>
#include<cstdlib>
#include<iostream>

LRock::LRock(glm::vec3 coords) {
	srand(time(NULL));
	trans = glm::translate(trans, coords);
	trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
	trans = glm::rotate(trans, float(rand() % 90), glm::vec3(0.0f, 1.0f, 0.0f));
	this->coords = coords;
	this->bound = Bounding::Bounding(15, 15, coords.x, coords.z);
}
glm::mat4 LRock::getTransform() {
	return this->trans;
}
Bounding LRock::getBoundaries() {
	return this->bound;
}
bool LRock::Fall(float DeltaTime) {
	float speed = DeltaTime * 300;
	if (this->coords.y > 0) {
		this->trans = glm::translate(trans, glm::vec3(0.0f, -speed, 0.0f));
		coords.y -= speed;
		return false;
	}
	else {
		if (!check) {
			check = true;
			return true;
		}
		else return false;

	}


}
