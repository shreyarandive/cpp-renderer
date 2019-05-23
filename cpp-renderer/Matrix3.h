#pragma once
#include "Vector3.h"

class Matrix3 
{
public:
	Vector3 rows[3];
	Matrix3() {};
	
	Matrix3 operator*(Matrix3 m);
	Matrix3 Inverted();
	Matrix3 Transposed();

	Vector3& operator[](int rowi);
	Vector3 operator*(Vector3 v);
	Vector3 GetColumn(int i);
	
	friend std::ostream& operator<<(std::ostream& os, Matrix3 m);
	
	void SetColumn(int i, Vector3 v);
};