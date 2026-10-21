#include "MiniHouse.h"
#include <gtx/transform.hpp>

MiniHouse::MiniHouse(glm::vec3 coords, float rotation) {

	trans = glm::translate(trans, coords);
	trans = glm::scale(trans, glm::vec3(180.0f, 180.0f, 180.0f));
	trans = glm::rotate(trans, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	this->coords = coords;
	if (rotation == 0) {
		Boundaries.push_back(Bounding::Bounding(27, 1, coords.x - 11, coords.z + 6.5));
		Boundaries.push_back(Bounding::Bounding(1, 26.5, coords.x - 36.5, coords.z + 31.5));
		Boundaries.push_back(Bounding::Bounding(27, 1, coords.x - 11, coords.z + 56));
		Boundaries.push_back(Bounding::Bounding(1, 11, coords.x + 14.5, coords.z + 47));
		Boundaries.push_back(Bounding::Bounding(1, 11, coords.x + 14.5, coords.z + 16));
	}
	if (int(rotation) % 360 == 90) {
		Boundaries.push_back(Bounding::Bounding(1, 27, coords.x + 6.5, coords.z + 11));
		Boundaries.push_back(Bounding::Bounding(26.5, 1, coords.x + 31.5, coords.z + 36.5));
		Boundaries.push_back(Bounding::Bounding(1, 27, coords.x + 56, coords.z + 11));
		Boundaries.push_back(Bounding::Bounding(11, 1, coords.x + 47, coords.z - 14.5));
		Boundaries.push_back(Bounding::Bounding(11, 1, coords.x + 16, coords.z - 14.5));

	}
	if (int(rotation) % 360 == 180) {
		Boundaries.push_back(Bounding::Bounding(27, 1, coords.x + 11, coords.z - 6.5));
		Boundaries.push_back(Bounding::Bounding(1, 26.5, coords.x + 36.5, coords.z - 31.5));
		Boundaries.push_back(Bounding::Bounding(27, 1, coords.x + 11, coords.z - 56));
		Boundaries.push_back(Bounding::Bounding(1, 11, coords.x - 14.5, coords.z - 47));
		Boundaries.push_back(Bounding::Bounding(1, 11, coords.x - 14.5, coords.z - 16));
	}
	if (int(rotation) % 360 == 270) {
		Boundaries.push_back(Bounding::Bounding(1, 27, coords.x - 6.5, coords.z - 11));
		Boundaries.push_back(Bounding::Bounding(26.5, 1, coords.x - 31.5, coords.z - 36.5));
		Boundaries.push_back(Bounding::Bounding(1, 27, coords.x - 56, coords.z - 11));
		Boundaries.push_back(Bounding::Bounding(11, 1, coords.x - 47, coords.z + 14.5));
		Boundaries.push_back(Bounding::Bounding(11, 1, coords.x - 16, coords.z + 14.5));
	}
}

glm::mat4 MiniHouse::getTransform() {
	return this->trans;
}
std::list<Bounding> MiniHouse::getBoundaries() {
	return this->Boundaries;
}
