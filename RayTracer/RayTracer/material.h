// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#ifndef MATERIAL_H_
#define MATERIAL_H_

#define DRAND ((double)rand() / RAND_MAX)	// случайное double число [0;+1]

#include "ray.h"
#include "hitable.h"

Vec3<double> randomInUnitSphere();
Vec3<double> reflect(const Vec3<double> & v, const Vec3<double> & n);

class Material {
public:
	virtual bool scatter(const Ray & rayIn, const HitRecord & rec, Vec3<double> & rayAttenuation, Ray & scattered) const = 0;
};

class Lambertian : public Material {
public:
	Lambertian(const Vec3<double> & albedo) : albedo_(albedo) {}
	virtual bool scatter(const Ray & rayIn, const HitRecord & rec, Vec3<double> & rayAttenuation, Ray & scattered) const {
		Vec3<double> target = rec.p + rec.normal + randomInUnitSphere();
		scattered = Ray(rec.p, target - rec.p);
		rayAttenuation = albedo_;

		return true;
	}

private:
	Vec3<double> albedo_;	// Albedo это доля падающего света, отражающегося от поверхности
				// низкий albedo	-->	темный обьект
				// высокий albedo	-->	светлый обьект
};

class Metal : public Material {
public:
	Metal(const Vec3<double>& albedo, double fuzziness) : albedo_(albedo) { 
		fuzziness_ = (fuzziness < 1) ? (fuzziness) : (1);
	}
	virtual bool scatter(const Ray & rayIn, const HitRecord & rec, Vec3<double> & rayAttenuation, Ray & scattered) const {
		Vec3<double> reflected = reflect( Vec3<double>::unitVector(rayIn.getDirection()), rec.normal);
		scattered = Ray(rec.p, reflected + randomInUnitSphere() * fuzziness_);
		rayAttenuation = albedo_;
		return (Vec3<double>::dotProduct(scattered.getDirection(), rec.normal) > 0);
	}
private:
	Vec3<double> albedo_;
	double fuzziness_;
};

Vec3<double> randomInUnitSphere() {
	Vec3<double> p;
	do {
		p = Vec3<double>(DRAND, DRAND, DRAND) * 2.0 - Vec3<double>(1, 1, 1);
	} while (Vec3<double>::dotProduct(p, p) >= 1.0);
	return p;
}

Vec3<double> reflect(const Vec3<double> & v, const Vec3<double> & n) {
	return v - n * Vec3<double>::dotProduct(v, n) * 2;
}

#endif	// MATERIAL_H_