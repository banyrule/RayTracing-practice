// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#ifndef RAY_H_
#define RAY_H_

#include "vec3.h"

class  Ray {

public:
	Ray() {}
	Ray(const Vec3<double> & rayOrigin, const Vec3<double> & rayDirection) { 
		origin = rayOrigin; 
		direction = rayDirection; 
	}

	Vec3<double> getOrigin() const { return origin; }
	Vec3<double> getDirection() const { return direction; }

	// луч это ф-ия p(t) = источкик + направление * время_t
	Vec3<double> pointAtParameter(double t) const { 
		return origin + direction * t; 
	}

private:
	Vec3<double> origin;
	Vec3<double> direction;
};

#endif	// RAY_H_