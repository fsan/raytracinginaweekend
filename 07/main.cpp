#include <iostream>
#include <float.h>
#include <random>

#include "sphere.hpp"
#include "camera.hpp"
#include "hitable_list.hpp"

using namespace std;

vec3<float> random_in_unit_sphere(){
    vec3<float> p;
    do{
	p = (float)2.0*vec3<float>(drand48(), drand48(), drand48()) - vec3<float>(1.0,1.0,1.0);

    }while(p.squared_length() >= 1.0);
    return p;
};

vec3<float> color(ray<float>& r, hitable<float> *world){
	hit_record<float> rec;
	if (world->hit(r, 0.001, MAXFLOAT,rec)) {
		vec3<float> target = rec.p + rec.normal + random_in_unit_sphere();
		auto ar = ray<float>(rec.p,target-rec.p);
		return (float)0.5 * color(ar, world);
	} else {
		vec3<float> unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return ((float)1.0 - t) * vec3<float>(1.0, 1.0, 1.0) + t * vec3<float>(0.5, 0.7, 1.0);
	}
}

int main(){
	int factor = 5;
	int nx = 200 * factor;
	int ny = 100 * factor;
	int ns = 100;
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

			float stat = (float)(-j+ny)/(float)ny ;
			std::cerr << stat << '\r';

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0 ;
}
