#pragma once
class Vector{
public:
	int x, y, z;
	int mirrored[8] = { 5,4,3,2,1,8,7,6 };
	Vector();
	Vector(int a, int b, int c);

	//Overload operators
	Vector operator+(int add);
	Vector operator*(int mult);
	friend bool operator==(Vector &v1, Vector &v2);
	Vector mirrorVec();
};

