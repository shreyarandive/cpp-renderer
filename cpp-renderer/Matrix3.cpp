#include "Matrix3.h"

Matrix3 Matrix3::operator*(Matrix3 m1)
{
	Matrix3 &m0 = *this; Matrix3 product;

	product.SetColumn(0, m0 * m1.GetColumn(0));
	product.SetColumn(1, m0 * m1.GetColumn(1));
	product.SetColumn(2, m0 * m1.GetColumn(2));

	return product;
}

Matrix3 Matrix3::Inverted()
{
	Matrix3 ret;
	Vector3 a = GetColumn(0), b = GetColumn(1), c = GetColumn(2);

	Vector3 _a = b ^ c; _a = _a / (a * _a);
	Vector3 _b = c ^ a; _b = _b / (b * _b);
	Vector3 _c = a ^ b; _c = _c / (c * _c);

	ret[0] = _a;
	ret[1] = _b;
	ret[2] = _c;

	return ret;
}

Matrix3 Matrix3::Transposed()
{
	Matrix3 ret;
	ret[0] = GetColumn(0);
	ret[1] = GetColumn(1);
	ret[2] = GetColumn(2);
	return ret;
}

Vector3& Matrix3::operator[](int rowi) 
{
	return rows[rowi];
}

Vector3 Matrix3::operator*(Vector3 v) 
{
	Matrix3 &m = *this;
	return Vector3(m[0] * v, m[1] * v, m[2] * v);
}

Vector3 Matrix3::GetColumn(int i)
{
	Matrix3 &m = *this;
	return Vector3(m[0][i], m[1][i], m[2][i]);
}

std::ostream& operator<<(std::ostream& ostr, Matrix3 m) 
{
	return ostr << m[0] << std::endl << m[1] << std::endl << m[2] << std::endl;
}

void Matrix3::SetColumn(int i, Vector3 v)
{
	Matrix3 &m = *this;
	m[0][i] = v[0];
	m[1][i] = v[1];
	m[2][i] = v[2];
}