#pragma once

#include "ray.hpp"

template <typename T>
class camera {
    public:
	camera(vec3<T> lookfrom, vec3<T> lookat, vec3<T> vup, T vfov, T aspect) {
	    vec3<T> u, v, w;

	    T theta = vfov*((T)M_PI/(T)180.0);
	    T half_height = tan(theta/2);
	    T half_width = aspect * half_height;

	    origin = lookfrom;
	    w = unit_vector(lookfrom - lookat);
	    u = unit_vector(cross(vup, w));
	    v = cross(w, u);

	    lower_left_corner = vec3<T>(-half_width, -half_height, -1.0);
	    lower_left_corner = origin - half_width*u - half_height*v - w;

	    horizontal = (T)2.0 * half_width * u;
	    vertical = (T)2.0 * half_height * v;
	}
	ray<T> get_ray(T u, T v) {
	    return ray<T>(origin, lower_left_corner + u*horizontal + v*vertical - origin);
	}

	vec3<T> origin;
	vec3<T> lower_left_corner;
	vec3<T> horizontal;
	vec3<T> vertical;

};

