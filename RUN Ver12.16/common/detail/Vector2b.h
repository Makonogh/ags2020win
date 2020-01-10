#include "..\Vector2.h"
template<class T>
Vector2Template<T>::Vector2Template()
{
	x = 0;
	y = 0;
}

template<class T>
Vector2Template<T>::Vector2Template(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<class T>
Vector2Template<T>::~Vector2Template()
{
}

template<class T>
Vector2Template<T> &Vector2Template<T>::operator=(const Vector2Template<T>& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

template<class T>
int & Vector2Template<T>::operator[](T i)
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

template<class T>
bool Vector2Template<T>::operator==(const Vector2Template<T> & vec) const
{
	return ((x == vec.x) && (y == vec.y));
}

template<class T>
bool Vector2Template<T>::operator!=(const Vector2Template<T> & vec) const
{
	return !((x == vec.x) && (y == vec.y)) ;
}

template<class T>
bool Vector2Template<T>::operator>(const Vector2Template<T> & vec) const
{
	return ((x > vec.x) && (y > vec.y));
}

template<class T>
bool Vector2Template<T>::operator>=(const Vector2Template<T> & vec) const
{
	return ((x >= vec.x) && (y >= vec.y));
}

template<class T>
Vector2Template<T> &Vector2Template<T>::operator+=(const Vector2Template<T> & vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template<class T>
Vector2Template<T> &Vector2Template<T>::operator-=(const Vector2Template<T> & vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<class T>
Vector2Template<T> &Vector2Template<T>::operator*=(T k)
{
	x *= k;
	y *= k;
	return *this;
}

template<class T>
Vector2Template<T> &Vector2Template<T>::operator/=(T k)
{
	x /= k;
	y /= k;
	return *this;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator+() const
{
	return *this;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator-() const
{
	return Vector2Template<T>(-this -> x,-this ->  y);
}

template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & v, T k)
{
	Vector2Template<T> vec;
	vec.x = v.x + k;
	vec.y = v.y + k;

	return vec;
}

template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & v, T k)
{
	Vector2Template<T>;
	vec.x = v.x - k;
	vec.y = v.y - k;

	return vec;
}

template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & v, T k)
{
	Vector2Template<T> vec;
	vec.x = v.x % k;
	vec.y = v.y % k;

	return vec;
}

template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & v, T k)
{
	Vector2Template<T> vec;
	vec.x = v.x * k;
	vec.y = v.y * k;

	return vec;
}

template<class T>
Vector2Template<T> operator*(T k, const Vector2Template<T> & v)
{
	Vector2Template<T> vec;
	vec.x = k * v.x;
	vec.y = k * v.y;

	return vec;
}

template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & v, T k)
{
	Vector2Template<T> vec;
	vec.x = v.x / k;
	vec.y = v.y / k;

	return vec;
}

template<class T>
inline Vector2Template<T>abs(const Vector2Template<T>& v)
{
	Vector2Template<T> vec;
	vec.x = abs(v.x);
	vec.y = abs(v.y);

	return vec;
}



