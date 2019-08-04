#include <iostream>
#include "ray.hpp"

using namespace std;
using vec3f = vec3<float>;

bool hit_sphere(const vec3<float>& center, float radius, const ray<float>& r){
    vec3<float> oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

auto color(ray<float>& r){
    if (hit_sphere(vec3<float>(0,0,-1), 0.5, r))
	return vec3<float>(1,0,0);
    auto unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return ((float)1.0 - t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5, 0.7, 1.0);
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

	for(int j = ny-1 ; j > 0 ; j--){
		for(int i = 0; i < nx; i++) {
			auto u = float(i) / float(nx);
			auto v = float(j) / float(ny);

			ray<float> r(origin, lower_left_corner + u * horizontal + v * vertical);
			auto col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0 ;
}
