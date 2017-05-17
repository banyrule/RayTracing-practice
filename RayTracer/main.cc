// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include "hitablelist.h"
#include "material.h"
#include "camera.h"
#include "sphere.h"

#define MAX_RAY_DEPTH 64

// вывод прогресбара в консоль (stderr)
void progressBarTick(double progress) {
	size_t barWidth = 32;
	std::cerr << int(progress * 100.0) << "% [";
	int pos = barWidth * progress;
	for (size_t i = 0; i < barWidth; ++i) {
		if (i <= pos) std::cerr << "=";
		else std::cerr << ".";
	}
	std::cerr << "] " << "\r";
	std::cerr.flush();
}

void progressBarDone() {
	size_t barWidth = 32;
	std::cerr << 100 << "% [";
	for (size_t i = 0; i < barWidth; ++i)
		std::cerr << "=";
	std::cerr << "] \033[032m OK" << std::endl;
}

Vec3<double> color(const Ray & r, Hitable *world, int depth) {
	HitRecord rec;
	if (world->hit(r, 0.0, 9000.0, rec)) {	// луч пересек какой-то обьект
		Ray scattered;
		Vec3<double> attenuation;
		if (depth < MAX_RAY_DEPTH && rec.material->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return Vec3<double>(0, 0, 0);
		}
	}
	else {	// луч ушел в закат - рисуется скайбокс
		Vec3<double> unitDirection = Vec3<double>::unitVector(r.getDirection());
		double t = 0.5 * (unitDirection.getY() + 1.0);
		return Vec3<double>(1.0, 1.0, 1.0) * (1.0 - t) + Vec3<double>(0.5, 0.7, 1.0) * t;	// градиент от синего к белому
	}
}

int main() {
	size_t imageWidth = 240;
	size_t imageHeight = 180;
	size_t samplesPerPixel = 128;	// кол-во проб на каждый пиксель (для сглаживания)

	std::cout << "P3" << std::endl;
	std::cout << imageWidth << " " << imageHeight << "\n255" << std::endl;

	Vec3<double> lowerLeftCorner(-2.0, -1.0, -1.0);		// левый нижний угол изображения во внутренних координатах
	Vec3<double> horizontal(4.0, 0.0, 0.0);			// ширина изображения во внутренних координатах
	Vec3<double> vertical(0.0, 2.0, 0.0);			// высота изображения во внутренних координатах
	Vec3<double> origin(0.0, 0.0, 0.0);			// положение камеры

	Hitable * list[4];

	list[0] = new Sphere(Vec3<double>(0, -100.5, -1), 100, new Lambertian(Vec3<double>(0.0, 0.6, 0.5)));
	list[1] = new Sphere(Vec3<double>(0, 0, -1), 0.5, new Lambertian(Vec3<double>(1.0, 1.0, 1.0)));
	list[2] = new Sphere(Vec3<double>(-1, 0, -1), 0.5, new Metal(Vec3<double>(1.0, 0.4, 0.0), 0.7));
	list[3] = new Sphere(Vec3<double>(1, 0, -1), 0.5, new Metal(Vec3<double>(1.0, 1.0, 1.0), 0.1));

	Hitable *world = new HitableList(list, 4);
	Camera cam(Vec3<double> (-1.7, 1.2, 1), Vec3<double>(0, 0, -1), Vec3<double>(0, 1, 0), 42, double(imageWidth)/double(imageHeight));

	for (size_t i = imageHeight; i > 0; --i) {
	
		progressBarTick(double(imageHeight - i) / imageHeight);
	
		for (size_t j = 0; j < imageWidth; ++j) {
			Vec3<double> col(0, 0, 0);
			for (size_t s = 0; s < samplesPerPixel; ++s) {
				double u = double(j + drand48()) / imageWidth;	// смещение по горизонтали
				double v = double(i + drand48()) / imageHeight;	// смещение по вертикали
				Ray r = cam.getRay(u, v);
				Vec3<double> p = r.pointAtParameter(2.0);
				col += color(r, world, 0);			// каждый пиксель собирается из нескольких проб
			}

			col /= double(samplesPerPixel);		// цвет проб усредняется, чтобы получить итоговый цвет
			col = Vec3<double>(sqrt(col.getR()), sqrt(col.getG()), sqrt(col.getB()));
			int ir = int(255.99 * col.getR());
			int ig = int(255.99 * col.getG());
			int ib = int(255.99 * col.getB());

			std::cout << ir << " " << ig << " " << ib << "\t";
		}
		std::cout << std::endl;
	}

	progressBarDone();

	return EXIT_FAILURE;
}