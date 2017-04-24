// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#ifndef HITABLE_H_
#define HITABLE_H_

#include "ray.h"

class Material;

struct HitRecord {
	double t;
	Vec3<double> p;
	Vec3<double> normal;
	Material * material;
	
};

class Hitable {
public:
	// t_min и t_max будут ограничивать область отрисовки
	virtual bool hit(const Ray & r, double tMin, double tMax, HitRecord & rec) const = 0;
};

#endif	// HITABLE_H_