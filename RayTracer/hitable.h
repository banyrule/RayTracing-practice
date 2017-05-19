// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#ifndef HITABLE_H_
#define HITABLE_H_

#include "ray.h"

class Material;

struct HitRecord
{
	double t;
	Vec3 p;
	Vec3 normal;
	Material * material;
};

class Hitable
{
public:
	// tMin и tMax будут ограничивать область отрисовки
	virtual bool hit(const Ray & r, double tMin, double tMax, HitRecord & rec) const = 0;
};

#endif	// HITABLE_H_
