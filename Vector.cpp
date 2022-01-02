#include "Vector.h"

Vector::Vector() {

}

Vector::Vector(int a, int b, int c) {
	this->x = a;
	this->y = b;
	this->z = c;
}

//Overload operators
Vector Vector::operator+(int add) {
	Vector ans;
	if (x + add <= 8) {
		ans.x = x + add;
	}
	else {
		ans.x = x + add - 8;
	}

	if (y + add <= 8) {
		ans.y = y + add;
	}
	else {
		ans.y = y + add - 8;
	}

	if (z + add <= 8) {
		ans.z = z + add;
	}
	else {
		ans.z = z + add - 8;
	}
	return ans;
}

bool operator==(Vector &v1, Vector &v2) {
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z) {
		return true;
	}
	else {
		return false;
	}
}

Vector Vector::mirrorVec() {
	Vector ans;
	ans.x = mirrored[x - 1];
	ans.y = mirrored[y - 1];
	ans.z = mirrored[z - 1];
	return ans;
}