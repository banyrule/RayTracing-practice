#ifndef VEC3_H_
#define VEC3_H_

#include <iostream>

template <class T> class Vec3
{
private:
	T x, y, z;

public:
	//
	// Конструкторы 
	//

	Vec3() { x = y = z = 0; };

	Vec3(T xValue, T yValue, T zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}

	//
	// Геттеры 
	//

	void set(const T & xValue, const T & yValue, const T & zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}

	T getX() const { return x; }
	T getY() const { return y; }
	T getZ() const { return z; }
	T getR() const { return x; }
	T getG() const { return y; }
	T getB() const { return z; }

	void setX(const T &xValue) { x = xValue; }
	void setY(const T &yValue) { y = yValue; }
	void setZ(const T &zValue) { z = zValue; }
	void setR(const T &xValue) { x = xValue; }
	void setG(const T &yValue) { y = yValue; }
	void setB(const T &zValue) { z = zValue; }

	//
	//  Вспомогательные методы
	//

	T magnitude() const {
		return sqrt((x * x) + (y * y) + (z * z));
	}

	T magnitudeSquared() const {
		(x * x) + (y * y) + (z * z);
	}

	void zero()
	{
		x = y = z = 0;
	}

	void normalise()
	{

		T magnitude = this->magnitude();

		if (magnitude != 0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
	}

	// Пример использования: double foo = Vec3<double>::dotProduct(vectorA, vectorB);
	static T dotProduct(const Vec3 & vec1, const Vec3 & vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	}

	// Пример использования: double foo = vectorA.dotProduct(vectorB);
	T dotProduct(const Vec3 & vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	// Пример использования: Vec3<double> crossVect = Vec3<double>::crossProduct(vectorA, vectorB);
	static Vec3 crossProduct(const Vec3 & vec1, const Vec3 & vec2)
	{
		return Vec3(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
	}

	void addX(T value) { x += value; }
	void addY(T value) { y += value; }
	void addZ(T value) { z += value; }

	// Расстояние между двумя векторами в пространстве
	//
	// Это не самая быстрая реализация (но точная). Для повышения скорости можно использовать
	// Manhattan Distance: http://en.wikipedia.org/wiki/Taxicab_geometry
	// double getManhattanDistance(Vec3 vec1, Vec3 vec2)
	// {
	//      float dx = abs(vec2.x - vec1.x);
	//      float dy = abs(vec2.y - vec1.y);
	//      float dz = abs(vec2.z - vec1.z);
	//      return dx + dy + dz;
	// }
	//
	static T getDistance(const Vec3 & vec1, const Vec3 & vec2)
	{
		T dx = vec2.x - vec1.x;
		T dy = vec2.y - vec1.y;
		T dz = vec2.z - vec1.z;

		return sqrt(dx * dx + dy * dy + dz * dz);
	}

	void display()
	{
		std::cout << "(" << x << ",\t" << y << ",\t" << z << ")" << std::endl;
	}

	//
	//  Перегруженные операторы
	//

	// WARNING: Операторы * и / предназначены для работы с векторами, задающими цвет.

	const Vec3& operator+() const {
		return *this;
	}

	inline Vec3 operator-() const {
		return Vec3<T>(-x, -y, -z);
	}

	Vec3 operator+(const Vec3 & vector) const
	{
		return Vec3<T>(x + vector.x, y + vector.y, z + vector.z);
	}

	Vec3 & operator+=(const Vec3 & vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;

		return *this;
	}

	Vec3 operator-(const Vec3 & vector) const
	{
		return Vec3<T>(x - vector.x, y - vector.y, z - vector.z);
	}

	Vec3 & operator-=(const Vec3 & vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return *this;
	}

	Vec3 operator*(const Vec3 & vector) const
	{
		return Vec3<T>(x * vector.x, y * vector.y, z * vector.z);
	}

	Vec3 & operator*=(const Vec3 & vector)
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;

		return *this;
	}

	Vec3 operator/(const Vec3 & vector) const
	{
		return Vec3<T>(x / vector.x, y / vector.y, z / vector.z);
	}

	Vec3 & operator/=(const Vec3 & vector)
	{
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;

		return *this;
	}

	Vec3 operator*(const T & value) const
	{
		return Vec3<T>(x * value, y * value, z * value);
	}

	Vec3 & operator*=(const T & value)
	{
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	Vec3 operator/(const T & value) const
	{
		return Vec3<T>(x / value, y / value, z / value);
	}

	Vec3 & operator/=(const T & value)
	{
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}
};

#endif	// VEC3_H_