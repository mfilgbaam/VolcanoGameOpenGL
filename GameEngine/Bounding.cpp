#include "Bounding.h"


Bounding::Bounding(float x, float z, float centerx, float centerz) {
	this->x = x;
	this->z = z;
	this->centerx = centerx;
	this->centerz = centerz;
}

bool Bounding::Collide(glm::vec3 pos) {
	float x = pos.x, z = pos.z;

	return ((x >= this->centerx && x < this->centerx + this->x) || (x < this->centerx&& x > this->centerx - this->x)) &&
		((z >= this->centerz && z < this->centerz + this->z) || (z < this->centerz&& z > this->centerz - this->z));
}
