#include "Vector3.h"
#include "Matrix3.h"

Vector3::Vector3(float x)
{
	vec3[0] = vec3[1] = vec3[2] = x;
}

Vector3::Vector3(float x, float y, float z)
{
	vec3[0] = x;
	vec3[1] = y;
	vec3[2] = z;
}

float& Vector3::operator[](int i)
{
	return vec3[i];
}

float Vector3::operator*(Vector3 v1) {

	Vector3 &v0 = *this;
	return v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2];

}

float Vector3::Magnitude()
{
	Vector3 &v = *this;
	return sqrt(v * v);
}

Vector3 Vector3::operator+(Vector3 v1)
{
	Vector3 &v0 = *this;
	return Vector3(v0[0] + v1[0], v0[1] + v1[1], v0[2] + v1[2]);
} 

Vector3 Vector3::operator-(Vector3 v1)
{
	Vector3 &v0 = *this;
	return Vector3(v0[0] - v1[0], v0[1] - v1[1], v0[2] - v1[2]);
}

Vector3 Vector3::operator^(Vector3 v1)
{
	Vector3 &v0 = *this;
	return Vector3 (v0[1] * v1[2] - v0[2] * v1[1],
					v0[2] * v1[0] - v0[0] * v1[2],
					v0[0] * v1[1] - v0[1] * v1[0]);
}

Vector3 Vector3::operator*(float scalar)
{
	Vector3 &v = *this;
	return Vector3(v[0] * scalar, v[1] * scalar, v[2] * scalar);
}

Vector3 Vector3::operator/(float scalar)
{
	Vector3 &v = *this;
	return Vector3(v[0] / scalar, v[1] / scalar, v[2] / scalar);
}


std::ostream& operator<<(std::ostream& os, Vector3 v)
{
	os << v[0] << " " << v[1] << " " << v[2];
	return os;
}

std::istream& operator>>(std::istream& is, Vector3& v) 
{
	is >> v[0] >> v[1] >> v[2];
	return is;
}

unsigned int Vector3::GetColor() 
{
	Vector3& v = *this;
	unsigned int ret = 0xFF000000;
	unsigned char* rgba = (unsigned char*)& ret;

	for (int i = 0 ; i < 3 ; i++) 
	{
		int ichan = (int)(255.0f * v[i]);
		ichan = (ichan < 0) ? 0 : ichan;
		ichan = (ichan > 255) ? 255 : ichan;
		rgba[i] = ichan;
	}

	return ret;
}


void Vector3::SetColor(unsigned int color)
{
	Vector3& v = *this;
	unsigned char* rgba = (unsigned char*)& color;
	
	v[0] = (float)rgba[0] / 255.0f;
	v[1] = (float)rgba[1] / 255.0f;
	v[2] = (float)rgba[2] / 255.0f;
}