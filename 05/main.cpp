#include <iostream>
#include "sphere.hpp"
#include "hitable_list.hpp"
#include <float.h>

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
	int factor = 2;
	int nx = 200 * factor;
	int ny = 100 * factor;
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	vec3<float> lower_left_corner(-2.0, -1.0, -1.0);
	vec3<float> horizontal(4.0, 0.0, 0.0);
	vec3<float> vertical(0.0, 2.0, 0.0);
	vec3<float> origin(0.0, 0.0, 0.0);

	hitable<float> *list[2];
	list[0] = new sphere<float>(vec3<float>(0,0,-1), 0.5);
	list[1] = new sphere<float>(vec3<float>(0,-100.5,-1), 100);

	hitable<float> *world = new hitable_list<float>(list,2);

	for(int j = ny-1 ; j > 0 ; j--){
		for(int i = 0; i < nx; i++) {
			auto u = float(i) / float(nx);
			auto v = float(j) / float(ny);

			ray<float> r(origin, lower_left_corner + u * horizontal + v * vertical);
			auto col = color(r, world);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0 ;
}
