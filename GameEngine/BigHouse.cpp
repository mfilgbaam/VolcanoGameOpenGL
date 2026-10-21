#include "BigHouse.h"
#include <gtx/transform.hpp>

BigHouse::BigHouse(glm::vec3 coords, float rotation) {

	trans = glm::translate(trans, coords);
	trans = glm::scale(trans, glm::vec3(180.0f, 180.0f, 180.0f));
	trans = glm::rotate(trans, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	this->coords = coords;
	if (rotation == 0) {
		Boundaries.push_back(Bounding::Bounding(35, 1, coords.x - 5, coords.z + 19));
		Boundaries.push_back(Bounding::Bounding(1, 21, coords.x + 32, coords.z + 40));
		Boundaries.push_back(Bounding::Bounding(1, 21, coords.x - 39, coords.z + 40));
		Boundaries.push_back(Bounding::Bounding(16, 1, coords.x - 25, coords.z + 63));
		Boundaries.push_back(Bounding::Bounding(17.5, 1, coords.x + 16.5, coords.z + 63));
		Boundaries.push_back(Bounding::Bounding(1, 15, coords.x - 26, coords.z + 76));
		Boundaries.push_back(Bounding::Bounding(1, 15, coords.x + 17, coords.z + 76));
		Boundaries.push_back(Bounding::Bounding(10, 1, coords.x - 19, coords.z + 90));
		Boundaries.push_back(Bounding::Bounding(10, 1, coords.x + 9, coords.z + 90));
	}
	if (int(rotation) % 360 == 90) {
		Boundaries.push_back(Bounding::Bounding(1, 35, coords.x + 19, coords.z + 5));
		Boundaries.push_back(Bounding::Bounding(21, 1, coords.x + 40, coords.z - 32));
		Boundaries.push_back(Bounding::Bounding(21, 1, coords.x + 40, coords.z + 39));
		Boundaries.push_back(Bounding::Bounding(1, 16, coords.x + 63, coords.z + 25));
		Boundaries.push_back(Bounding::Bounding(1, 17.5, coords.x + 63, coords.z - 16.5));
		Boundaries.push_back(Bounding::Bounding(15, 1, coords.x + 76, coords.z + 26));
		Boundaries.push_back(Bounding::Bounding(15, 1, coords.x + 76, coords.z - 17));
		Boundaries.push_back(Bounding::Bounding(1, 10, coords.x + 90, coords.z + 19));
		Boundaries.push_back(Bounding::Bounding(1, 10, coords.x + 90, coords.z - 9));
	}
	if (int(rotation) % 360 == 180) {
		Boundaries.push_back(Bounding::Bounding(35, 1, coords.x + 5, coords.z - 19));
		Boundaries.push_back(Bounding::Bounding(1, 21, coords.x - 32, coords.z - 40));
		Boundaries.push_back(Bounding::Bounding(1, 21, coords.x + 39, coords.z - 40));
		Boundaries.push_back(Bounding::Bounding(16, 1, coords.x + 25, coords.z - 63));
		Boundaries.push_back(Bounding::Bounding(17.5, 1, coords.x - 16.5, coords.z - 63));
		Boundaries.push_back(Bounding::Bounding(1, 15, coords.x + 26, coords.z - 76));
		Boundaries.push_back(Bounding::Bounding(1, 15, coords.x - 17, coords.z - 76));
		Boundaries.push_back(Bounding::Bounding(10, 1, coords.x + 19, coords.z - 90));
		Boundaries.push_back(Bounding::Bounding(10, 1, coords.x - 9, coords.z - 90));
	}
	if (int(rotation) % 360 == 270) {
		Boundaries.push_back(Bounding::Bounding(1, 35, coords.x - 19, coords.z - 5));
		Boundaries.push_back(Bounding::Bounding(21, 1, coords.x - 40, coords.z + 32));
		Boundaries.push_back(Bounding::Bounding(21, 1, coords.x - 40, coords.z - 39));
		Boundaries.push_back(Bounding::Bounding(1, 16, coords.x - 63, coords.z - 25));
		Boundaries.push_back(Bounding::Bounding(1, 17.5, coords.x - 63, coords.z + 16.5));
		Boundaries.push_back(Bounding::Bounding(15, 1, coords.x - 76, coords.z - 26));
		Boundaries.push_back(Bounding::Bounding(15, 1, coords.x - 76, coords.z + 17));
		Boundaries.push_back(Bounding::Bounding(1, 10, coords.x - 90, coords.z - 19));
		Boundaries.push_back(Bounding::Bounding(1, 10, coords.x - 90, coords.z + 9));
	}
}

glm::mat4 BigHouse::getTransform() {
	return this->trans;
}
std::list<Bounding> BigHouse::getBoundaries() {
	return this->Boundaries;
}
