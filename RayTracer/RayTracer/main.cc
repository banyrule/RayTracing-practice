// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "vec3.h"
#include "ray.h"

double hitSphere(const Vec3<double> center, double radius, const ray & r) {
	Vec3<double> oc = r.getOrigin() - center;	// направление от источника луча к центру сферы
	// коф-цы квадратного уравнения, задающего точки пересечения луча со сферой
	double a = Vec3<double>::dotProduct(r.getDirection(), r.getDirection());
	double b = 2.0 * Vec3<double>::dotProduct(oc, r.getDirection());
	double c = Vec3<double>::dotProduct(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	// D = 0 -> луч коснулся сферы один раз
	// D > 0 -> луч пересек сферу в двух точках
	// D < 0 -> луч не попал в сферу
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant)) / (2.0 * a);	// параметр t, при котором луч пересекает сферу
	}
}

Vec3<double> skyboxColor(const ray & r) {

	Vec3<double> sphereCenter = Vec3<double>(0, 0, -1);
	double sphereRadius = 0.5;
	// луч попал в сферу
	double t = hitSphere(sphereCenter, sphereRadius, r);
	if (t > 0.0) {
		Vec3<double> N = Vec3<double>::unitVector(r.pointAtParameter(t) - sphereCenter);	// нормаль отражения
		return Vec3<double>(N.getX() + 1, N.getY() + 1, N.getZ() + 1) * 0.5;
	}

	// луч не попал в сферу - рисуется скайбокс
	Vec3<double> unitDirection = Vec3<double>::unitVector(r.getDirection());
	t = 0.5 * (unitDirection.getY() + 1.0);
	return Vec3<double>(1.0, 1.0, 1.0) * (1.0 - t) + Vec3<double>(0.5, 0.7, 1.0) * t;	// градиент от синего к белому
}


int main() {
	freopen("test.ppm", "w", stdout);

	size_t image_with = 640;
	size_t image_height = 320;

	std::cout << "P3" << std::endl;
	std::cout << image_with << " " << image_height << "\n255" << std::endl;

	Vec3<double> lowerLeftCorner(-2.0, -1.0, -1.0);		// левый нижний угол изображения во внутренних координатах
	Vec3<double> horizontal(4.0, 0.0, 0.0);			// ширина изображения во внутренних координатах
	Vec3<double> vertical(0.0, 2.0, 0.0);			// высота изображения во внутренних координатах
	Vec3<double> origin(0.0, 0.0, 0.0);			// положение камеры


	for (size_t i = image_height; i > 0; --i) {
		for (size_t j = 0; j < image_with; ++j) {
			double u = double(j) / image_with;	// смещение по горизонтали
			double v = double(i) / image_height;	// смещение по вертикали
			ray r(origin, lowerLeftCorner + horizontal * u + vertical * v);
			Vec3<double> col = skyboxColor(r);

			int ir = int(255.99 * col.getR());
			int ig = int(255.99 * col.getG());
			int ib = int(255.99 * col.getB());
			std::cout << ir << " " << ig << " " << ib << "\t";
		}
		std::cout << std::endl;
	}

	return EXIT_FAILURE;
}