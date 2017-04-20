// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "vec3.h"
#include "ray.h"

bool hitSphere(const Vec3<double> center, double radius, const ray & r) {
	Vec3<double> oc = r.getOrigin() - center;	// направление от источника луча к центру сферы
	// квадратное уравнение, задающее точки пересечения луча со сферой
	double a = Vec3<double>::dotProduct(r.getDirection(), r.getDirection());
	double b = 2.0 * Vec3<double>::dotProduct(oc, r.getDirection());
	double c = Vec3<double>::dotProduct(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	// D = 0 -> луч коснулся сферы один раз
	// D > 0 -> луч пересек сферу в двух точках
	// D < 0 -> луч не попал в сферу
	return (discriminant > 0);
}

Vec3<double> skyboxColor(const ray & r) {

	// луч попал в сферу
	if (hitSphere(Vec3<double>(0, 0, -1), 0.5, r))
		return Vec3<double>(1, 0, 0);	// пока простая заглушка. Графон завезу потом

	// луч не попал в сферу - рисуется скайбокс
	Vec3<double> unitDirection = Vec3<double>::unitVector(r.getDirection());
	double t = 0.5 * (unitDirection.getY() + 1.0);
	return Vec3<double>(1.0, 1.0, 1.0) * (1.0 - t) + Vec3<double>(0.5, 0.7, 1.0) * t;	// градиент от синего к белому
}


int main() {
	freopen("test.ppm", "w", stdout);


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