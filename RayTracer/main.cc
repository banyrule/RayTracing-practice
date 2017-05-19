#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"


Vec3 color(const Ray & r, Hitable * world, int depth) {
    HitRecord rec;
    if (world->hit(r, 0.001, 9000, rec)) { 
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
             return attenuation*color(scattered, world, depth+1);
        }
        else {
            return Vec3(0,0,0);
        }
    }
    else {
        Vec3 unit_direction = unitVector(r.getDirection());
        double t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
    }
}

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

int main() {
    int imageWidth = 640;
    int imageHeight = 320;
    int samplesPerPixel = 8;

    
    Hitable * list[5];
    list[0] = new Sphere(Vec3(0,-100.5,-1), 100, new Lambertian(Vec3(0.0, 0.6, 0.5)));
    list[1] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(1.0, 1.0, 1.0)));
	list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(1.0, 0.4, 0.0), 0.7));
    list[3] = new Sphere(Vec3(-1,0,-1), 0.5, new Dielectric(2.4));
    list[4] = new Sphere(Vec3(-1,0,-1), -0.45, new Dielectric(2.4));
    Hitable * world = new HitableList(list,5);

    Vec3 lookFrom(-3, 1.5, 2);
    Vec3 lookAt(0, 0, -1);
    double vFow = 20;
    double focusDist = (lookFrom - lookAt).length();
    double aperture = 0.1;

    Camera cam(lookFrom, lookAt, Vec3(0,1,0), vFow, double(imageWidth)/double(imageHeight), aperture, focusDist);

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255" << std::endl;
    for (size_t i = imageHeight-1; i > 0; --i) {
        
        progressBarTick(double(imageHeight - i) / imageHeight);
        
        for (size_t j = 0; j < imageWidth; ++j) {
            Vec3 col(0, 0, 0);

            for (size_t s = 0; s < samplesPerPixel; ++s) {
                double u = double(j + drand48()) / double(imageWidth);
                double v = double(i + drand48()) / double(imageHeight);
                Ray r = cam.getRay(u, v);
                Vec3 p = r.pointAtParameter(2.0);
                col += color(r, world,0);
            }

            col /= double(samplesPerPixel);
            col = Vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            
            int r = int(255.99*col[0]); 
            int g = int(255.99*col[1]); 
            int b = int(255.99*col[2]); 

            std::cout << r << " " << g << " " << b << "\t";   
        }
        std::cout << std::endl;
    }

    progressBarDone();
    return EXIT_SUCCESS;
}



