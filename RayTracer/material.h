// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#ifndef MATERIAL_H_
#define MATERIAL_H_

struct HitRecord;

#include "ray.h"
#include "hitable.h"


double schlick(double cosine, double refractiveIndex_) {
	double r0 = (1 - refractiveIndex_) / (1 + refractiveIndex_);
	r0 = r0 * r0;

	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool refract(const Vec3 & v, const Vec3 & n, double niOverNt, Vec3 & refracted) {
	Vec3 uv = unitVector(v);
	double dt = dot(uv, n);
	double discriminant = 1.0 - niOverNt * niOverNt * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = niOverNt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else 
		return false;
}


Vec3 reflect(const Vec3 & v, const Vec3 & n) {
	return v - 2 * dot(v, n) * n;
}


Vec3 randomInUnitSphere() {
	Vec3 p;
	do {
		p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
	} while (p.squaredLength() >= 1.0);
	
	return p;
}


class Material  {
public:
	virtual bool scatter(const Ray & rayIn, const HitRecord & rec, Vec3 & rayAttenuation, Ray & scattered) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const Vec3& albedo) : albedo_(albedo) {}

        virtual bool scatter(const Ray & rayIn, const HitRecord & rec, Vec3 & rayAttenuation, Ray & scattered) const  {
             Vec3 target = rec.p + rec.normal + randomInUnitSphere();
             scattered = Ray(rec.p, target-rec.p);
             rayAttenuation = albedo_;

             return true;
        }
private:
        Vec3 albedo_;
	// Albedo это доля падающего света, отражающегося от поверхности
	// низкий albedo	-->	темный обьект
	// высокий albedo	-->	светлый обьект
};

class Metal : public Material {
public:
	Metal(const Vec3 & albedo, double fuzziness) : albedo_(albedo) { 
		fuzziness_ = (fuzziness < 1) ? (fuzziness) : (1);
	}

	virtual bool scatter(const Ray & rayIn, const HitRecord & rec, Vec3 & rayAttenuation, Ray & scattered) const  {
		Vec3 reflected = reflect(unitVector(rayIn.getDirection()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzziness_ * randomInUnitSphere());
		rayAttenuation = albedo_;

		return (dot(scattered.getDirection(), rec.normal) > 0);
	}
private:
	Vec3 albedo_;
	double fuzziness_;
};

class Dielectric : public Material { 
public:
	Dielectric(double refractiveIndex) : refractiveIndex_(refractiveIndex) {}
    
	virtual bool scatter(const Ray & rayIn, const HitRecord & rec, Vec3 & rayAttenuation, Ray & scattered) const  {
		Vec3 outwardNormal;
		Vec3 reflected = reflect(rayIn.getDirection(), rec.normal);
		Vec3 refracted;
		double niOverNt;	 
		double reflectionProbe;
		double cosine;
		rayAttenuation = Vec3(1.0, 1.0, 1.0); 

		if (dot(rayIn.getDirection(), rec.normal) > 0) {
			outwardNormal = -rec.normal;
			niOverNt = refractiveIndex_;
			cosine = dot(rayIn.getDirection(), rec.normal) / rayIn.getDirection().length();
			cosine = sqrt(1 - refractiveIndex_*refractiveIndex_*(1-cosine*cosine));
		}
		else {
			outwardNormal = rec.normal;
			niOverNt = 1.0 / refractiveIndex_;
			cosine = -dot(rayIn.getDirection(), rec.normal) / rayIn.getDirection().length();
		}
		
		if (refract(rayIn.getDirection(), outwardNormal, niOverNt, refracted)) 
			reflectionProbe = schlick(cosine, refractiveIndex_);
		else 
			reflectionProbe = 1.0;
		if (drand48() < reflectionProbe) 
			scattered = Ray(rec.p, reflected);
		else 
			scattered = Ray(rec.p, refracted);

	return true;
    }
    
private:
	double refractiveIndex_;
};

#endif




