// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "hitablelist.h"
#include "camera.h"
#include "sphere.h"


Vec3<double> color(const Ray & r, Hitable *world) {
	HitRecord rec;
		return Vec3<double>(rec.normal.getX() + 1, rec.normal.getY() + 1, rec.normal.getZ() + 1) * 0.5;
	}
	else {	// луч ушел в закат - рисуется скайбокс
		Vec3<double> unitDirection = Vec3<double>::unitVector(r.getDirection());
		double t = 0.5 * (unitDirection.getY() + 1.0);
		return Vec3<double>(1.0, 1.0, 1.0) * (1.0 - t) + Vec3<double>(0.5, 0.7, 1.0) * t;	// градиент от синего к белому
	}
}

int main() {
	freopen("test.ppm", "w", stdout);

	size_t imageWidth = 640;
	size_t imageHeight = 320;
	size_t samplesPerPixel = 16; // кол-во проб на каждый пиксель (для сглаживания)

	std::cout << "P3" << std::endl;
	std::cout << imageWidth << " " << imageHeight << "\n255" << std::endl;

	Vec3<double> lowerLeftCorner(-2.0, -1.0, -1.0);		// левый нижний угол изображения во внутренних координатах
	Vec3<double> horizontal(4.0, 0.0, 0.0);			// ширина изображения во внутренних координатах
	Vec3<double> vertical(0.0, 2.0, 0.0);			// высота изображения во внутренних координатах
	Vec3<double> origin(0.0, 0.0, 0.0);			// положение камеры

	Hitable *list[2];

	list[0] = new Sphere(Vec3<double>(0, 0, -1), 0.5);
	list[1] = new Sphere(Vec3<double>(0, -100.5, -1), 100);

	Hitable *world = new HitableList(list, 2);

	for (size_t i = imageHeight; i > 0; --i) {
		fprintf(stderr, "RENDER PROCESS: %f\n",  double(imageHeight - i) / imageHeight * 100);
		for (size_t j = 0; j < imageWidth; ++j) {
			Vec3<double> col(0, 0, 0);
			for (size_t s = 0; s < samplesPerPixel; ++s) {
				double u = double(j + (double)rand() / RAND_MAX) / imageWidth;	// смещение по горизонтали
				double v = double(i + (double)rand() / RAND_MAX) / imageHeight;	// смещение по вертикали
				Ray r = cam.getRay(u, v);
				Vec3<double> p = r.pointAtParameter(2.0);
				col += color(r, world);			// каждый пиксель собирается из нескольких проб
			}

			col /= double(samplesPerPixel);		// цвет проб усредняется, чтобы получить итоговый цвет
			int ir = int(255.99 * col.getR());
			int ig = int(255.99 * col.getG());
			int ib = int(255.99 * col.getB());

			std::cout << ir << " " << ig << " " << ib << "\t";
		}
		std::cout << std::endl;
	}

	return EXIT_FAILURE;
}