#include "Vector2.h"


Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(int x, int y)
{
	Vector2::x = x;
	Vector2::y = y;
}


Vector2::~Vector2()
{
}

Vector2 & Vector2::operator=(const Vector2 & vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

int & Vector2::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1) 
	{
		return y;
	}
	else
	{
		return x;
	}
}

bool Vector2::operator==(const Vector2 & vec) const
{
	return ((x == vec.x) && (y == vec.y));
}

bool Vector2::operator!=(const Vector2 & vec) const
{
	return !((x == vec.x) && (y == vec.y)) ;
}

bool Vector2::operator>(const Vector2 & vec) const
{
	return ((x > vec.x) && (y > vec.y));
}

bool Vector2::operator>=(const Vector2 & vec) const
{
	return ((x >= vec.x) && (y >= vec.y));
}

Vector2 & Vector2::operator+=(const Vector2 & vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2 & Vector2::operator*=(int k)
{
	x *= k;
	y *= k;
	return *this;
}

Vector2 & Vector2::operator/=(int k)
{
	x /= k;
	y /= k;
	return *this;
}

Vector2 Vector2::operator+() const
{
	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-this -> x,-this ->  y);
}

Vector2 operator+(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}

Vector2 operator-(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}

Vector2 operator*(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;

	return vec;
}

Vector2 operator/(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;

	return vec;
}

Vector2 operator%(const Vector2 & u, const Vector2 & v)
{
	Vector2 vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;

	return vec;
}

Vector2 operator+(const Vector2 & v, int k)
{
	Vector2 vec;
	vec.x = v.x + k;
	vec.y = v.y + k;

	return vec;
}

Vector2 operator-(const Vector2 & v, int k)
{
	Vector2 vec;
	vec.x = v.x - k;
	vec.y = v.y - k;

	return vec;
}

Vector2 operator%(const Vector2 & v, int k)
{
	Vector2 vec;
	vec.x = v.x % k;
	vec.y = v.y % k;

	return vec;
}

Vector2 operator*(const Vector2 & v, int k)
{
	Vector2 vec;
	vec.x = v.x * k;
	vec.y = v.y * k;

	return vec;
}

Vector2 operator*(int k, const Vector2 & v)
{
	Vector2 vec;
	vec.x = k * v.x;
	vec.y = k * v.y;

	return vec;
}

Vector2 operator/(const Vector2 & v, int k)
{
	Vector2 vec;
	vec.x = v.x / k;
	vec.y = v.y / k;

	return vec;
}
