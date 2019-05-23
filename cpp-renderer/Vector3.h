#pragma once

#include <iostream>

class Vector3 
{
public:
	float vec3[3];
	
	Vector3() {};
	Vector3(float x);
	Vector3(float x, float y, float z);

	float& operator[](int i);
	float operator*(Vector3 v);
	float Magnitude();
	
	Vector3 operator+(Vector3 v);
	Vector3 operator-(Vector3 v);
	Vector3 operator^(Vector3 v);
	Vector3 operator*(float scalar);
	Vector3 operator/(float scalar);
	
	friend std::ostream& operator<<(std::ostream& os, Vector3 v);
	friend std::istream& operator>>(std::istream& is, Vector3& v);

	unsigned int GetColor();

	void SetColor(unsigned int color);
};