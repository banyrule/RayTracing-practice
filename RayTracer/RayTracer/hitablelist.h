// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#ifndef HITABLELIST_H_
#define HITABLELIST_H_

#include "hitable.h"

class HitableList : public Hitable {
public:
	HitableList() {}
	HitableList(Hitable ** list, int n) : list_(list), listSize_(n) {}
	virtual bool hit(const Ray & r, double tMin, double tMax, HitRecord & rec) const;

private:
	Hitable ** list_;
	size_t listSize_;
};

bool HitableList::hit(const Ray & r, double tMin, double tMax, HitRecord & rec) const {
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = tMax;	// ближайшая точка, в которую попал луч

	for (size_t i = 0; i < listSize_; ++i) {
		if (list_[i]->hit(r, tMin, closestSoFar, tempRec)) {
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}

#endif	// HITABLELIST_H_