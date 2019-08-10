#include <iostream>
#include <float.h>
#include <random>

#include "sphere.hpp"
#include "camera.hpp"
#include "hitable_list.hpp"

using namespace std;


vec3<float> color(ray<float>& r, hitable<float> *world){
	hit_record<float> rec;
	if (world->hit(r, 0.0, MAXFLOAT,rec)) {
		return (float)0.5 * vec3<float>(rec.normal.x()+1.0, rec.normal.y()+1.0, rec.normal.z()+1.0);
	} else {
		vec3<float> unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return ((float)1.0 - t) * vec3<float>(1.0, 1.0, 1.0) + t * vec3<float>(0.5, 0.7, 1.0);
	}
}

int main(){
	int factor = 3;
	int nx = 200 * factor;
	int ny = 100 * factor;
	int ns = 100;

	auto tot = nx*ny*ns;
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	hitable<float> *list[2];
	list[0] = new sphere<float>(vec3<float>(0,0,-1), 0.5);
	list[1] = new sphere<float>(vec3<float>(0,-100.5,-1), 100);

	hitable<float> *world = new hitable_list<float>(list,2);
	camera<float> cam;

	for(int j = ny-1 ; j > 0 ; j--){
		for(int i = 0; i < nx; i++) {
			vec3<float> col(0,0,0);

			for(int s = 0; s < ns; s++) {
			    std::cerr << (float)(j*i*s)/(float)tot << "\r";
			    auto u = float(i + drand48()) / float(nx);
			    auto v = float(j + drand48()) / float(ny);

			    ray<float> r = cam.get_ray(u,v);
			    //? vec3<float> p = r.point_at_parameter(2.0);
			    col += color(r, world);
			}
			col /= float(ns);

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0 ;
}
