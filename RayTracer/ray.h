// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#ifndef RAY_H_
#define RAY_H_

#include "vec3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Vec3 & origin, const Vec3 & direction) : origin_(origin), direction_(direction) {}  
	
	Vec3 getOrigin() const	{ return origin_; }
	Vec3 getDirection() const	{ return direction_; }

	// луч это ф-ия p(t) = источкик + направление * время_t
	Vec3 pointAtParameter(double t) const { return origin_ + t*direction_; }
private:
	Vec3 origin_;
	Vec3 direction_;
};

#endif	// RAY_H_


