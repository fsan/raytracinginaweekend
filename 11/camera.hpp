#pragma once

#include "common.hpp"
#include "ray.hpp"

template <typename T>
vec3<T> random_in_unit_disk() {
    vec3<T> p;
    do {
	p = (T)2.0 * vec3<T>(fRand_fast(), fRand_fast(), 0) - vec3<T>(1,1,0);
    } while(dot(p,p) >= 1.0);
    return p;
}

template <typename T>
class camera {
    public:
	camera(vec3<T> lookfrom,
	       vec3<T> lookat,
	       vec3<T> vup,
	       T vfov,
	       T aspect,
	       T aperture,
	       T focus_dist) {

	    lens_radius = aperture /2;


	    T theta = vfov*((T)M_PI/(T)180.0);
	    T half_height = tan(theta/2);
	    T half_width = aspect * half_height;

	    origin = lookfrom;
	    w = unit_vector(lookfrom - lookat);
	    u = unit_vector(cross(vup, w));
	    v = cross(w, u);

	    lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;

	    horizontal = (T)2.0 * half_width * focus_dist * u;
	    vertical = (T)2.0 * half_height * focus_dist * v;
	}
	ray<T> get_ray(T s, T t) {
	    vec3<T> rd = lens_radius * random_in_unit_disk<T>();
	    vec3<T> offset = u * rd.x() + v * rd.y();
	    return ray<T>(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
	}

	vec3<T> origin;
	vec3<T> lower_left_corner;
	vec3<T> horizontal;
	vec3<T> vertical;
	vec3<T> u, v, w;

	T lens_radius;

};

