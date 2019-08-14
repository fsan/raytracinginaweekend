#include <iostream>
#include <float.h>
#include <random>

#include "material.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "hitable_list.hpp"

using namespace std;

vec3<float> color(ray<float>& r, hitable<float> *world, int depth){
	hit_record<float> rec;
	if (world->hit(r, 0.001, MAXFLOAT,rec)) {
		ray<float> scattered;
		vec3<float> attenuation;

		if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
			
			return attenuation*color(scattered, world, depth+1);
		}
		else {
			return vec3<float>(0.0, 0.0, 0.0);
		}
	}
	else {
		vec3<float> unit_direction = unit_vector(r.direction());
		float t = 0.5 *(unit_direction.y() + 1.0);
		return (float)(1.0-t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5,0.7,1.0);
	}
}

int main(){
	int factor = 5;
	int nx = 200 * factor;
	int ny = 100 * factor;
	int ns = 100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	hitable<float> *list[2];
	auto mat1 = new lambertian<float>(vec3<float>(0.8,0.3,0.3));
	auto mat2 = new lambertian<float>(vec3<float>(0.8,0.8,0.0));
	list[0] = new sphere<float>(vec3<float>(0,0,-1), 0.5, mat1);
	list[1] = new sphere<float>(vec3<float>(0,-100.5,-1), 100, mat2);

	hitable<float> *world = new hitable_list<float>(list,2);
	camera<float> cam;

	for(int j = ny-1 ; j > 0 ; j--){
		for(int i = 0; i < nx; i++) {
			vec3<float> col(0,0,0);

			for(int s = 0; s < ns; s++) {
			    auto u = float(i + drand48()) / float(nx);
			    auto v = float(j + drand48()) / float(ny);

			    ray<float> r = cam.get_ray(u,v);
			    col += color(r, world,0);
			}
			col /= float(ns);

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);


			std::cout << ir << " " << ig << " " << ib << "\n";
		}
		float stat = (float)(-j+ny)/(float)ny ;
		std::cerr << (ny-j) << " " << stat << '\r';
	}
	return 0 ;
}
