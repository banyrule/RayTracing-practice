// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#ifndef SPHERE_H_
#define SPHERE_H_

#include "hitable.h"

class Sphere : public Hitable {
public:
	Sphere() {}
	Sphere(Vec3<double> center, double radius) : center(center), radius(radius) {};
	virtual bool hit(const Ray & r, double tMin, double tMax, HitRecord & rec) const;
// private:
	Vec3<double> center;
	double radius;
};

bool Sphere::hit(const Ray & r, double tMin, double tMax, HitRecord & rec) const {
	Vec3<double> oc = r.getOrigin() - center;	// направление от источника луча к центру сферы
	// коэффициенты квадратного уравнения, задающего точки пересечения луча со сферой
	double a = Vec3<double>::dotProduct(r.getDirection(), r.getDirection());
	double b = 2.0 * Vec3<double>::dotProduct(oc, r.getDirection());
	double c = Vec3<double>::dotProduct(oc, oc) - radius * radius;
	double discriminant = (b * b) - 4*(a * c);
	// D = 0 -> луч коснулся сферы один раз
	// D > 0 -> луч пересек сферу в двух точках
	// D < 0 -> луч не попал в сферу
	if (discriminant > 0) {
		// луч пересек сферу. Проверка на область отрисовки
		double temp = (-b - sqrt(discriminant)) / (2 * a);
		if (temp < tMax && temp > tMin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius; // нормаль в точке на сфере сонаправлена с вектором от центра к точке
			return true;
		}
		temp = (-b + sqrt(discriminant)) / (2 * a);
		if (temp < tMax && temp > tMin) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}

	return false;
}

#endif	// SPHERE_H_