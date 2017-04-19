// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int main() {
	freopen("test.ppm", "w", stdout);

	size_t image_with = 320;
	size_t image_height = 320;

	std::cout << "P3" << std::endl;
	std::cout << image_with << " " << image_height << "\n255" << std::endl;

	for (size_t i = image_height; i > 0; --i) {
		for (size_t j = 0; j < image_with; ++j) {
			double r = double(j) / double(image_with);
			double g = double(i) / double(image_height);
			double b = 0.2;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			std::cout << ir << " " << ig << " " << ib << "\t";
		}
		std::cout << std::endl;
	}

	return EXIT_FAILURE;
}