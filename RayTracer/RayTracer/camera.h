// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"

#define _USE_MATH_DEFINES
#include <math.h> // число pi


class Camera {
public:
	Camera(Vec3<double> lookFrom, Vec3<double> lookAt, Vec3<double> viewUp,double vFow, double aspect) {	// vFow угол зрения от нижнего края до верхнего
		Vec3<double> u, v, w;	// ортогональный базис камеры						// viewUp != world up (0, 1, 0)
		double theta = vFow * M_PI / 180;
		double halfHeight = tan(theta / 2);
		double halfWidth = aspect * halfHeight;

		origin_ = lookFrom;
		w = Vec3<double>::unitVector(lookFrom - lookAt);
		u = Vec3<double>::unitVector( Vec3<double>::crossProduct(viewUp, w) );
		v = Vec3<double>::crossProduct(w, u);	

		lowerLeftCorner_ = origin_ - u * halfWidth - v * halfHeight - w;
		horizontal_ = u * halfWidth * 2;
		vertical_ = v * halfHeight * 2;
	}

	Ray getRay(double u, double v) {
		return Ray(origin_, lowerLeftCorner_ + horizontal_ * u + vertical_ * v - origin_);
	}

private:
	Vec3<double> origin_;
	Vec3<double> lowerLeftCorner_;
	Vec3<double> horizontal_;
	Vec3<double> vertical_;
};

#endif	// CAMERA_H_