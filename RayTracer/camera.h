// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"

Vec3 randomInUnitDisk() {
	Vec3 p;
	do {
		p = 2.0*Vec3(drand48(),drand48(),0) - Vec3(1,1,0);
	} while (dot(p,p) >= 1.0);
	
	return p;
}

class Camera {
public:
	Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 viewUp, double verticalFow,       	// vFow угол зрения от нижнего края до верхнего
				double aspect, double aperture, double focus_dist) {    // viewUp != world up (0, 1, 0)	
		
		lensRadius_ = aperture / 2;
		double theta = verticalFow * M_PI / 180;
		double half_height = tan(theta / 2);
		double half_width = aspect * half_height;
		origin_ = lookFrom;
		w_ = unitVector(lookFrom - lookAt);
		u_ = unitVector(cross(viewUp, w_));
		v_ = cross(w_, u_);
		lowerLeftCorner_ = origin_ - half_width * focus_dist * u_ - half_height * focus_dist * v_ - focus_dist * w_;
		horizontal_ = 2 * half_width * focus_dist * u_;
		vertical_ = 2 * half_height * focus_dist * v_;
	}

	Ray getRay(double s, double t) {
		Vec3 rd = lensRadius_*randomInUnitDisk();
		Vec3 offset = u_ * rd.x() + v_ * rd.y();
		
		return Ray(origin_ + offset, lowerLeftCorner_ + s * horizontal_ + t * vertical_ - origin_ - offset); 
	}

private:
	Vec3 origin_;
	Vec3 lowerLeftCorner_;
	Vec3 horizontal_;
	Vec3 vertical_;
	Vec3 u_, v_, w_;
	double lensRadius_;
};

#endif	// CAMERA_H_




