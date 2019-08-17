#pragma once

#include "ray.hpp"

template <typename T>
class camera {
    public:
	camera(T vfov, T aspect) {
	    T theta = vfov*((T)M_PI/(T)180.0);
	    T half_height = tan(theta/2);
	    T half_width = aspect * half_height;

	    lower_left_corner = vec3<T>(-half_width, -half_height, -1.0);
	    horizontal = vec3<T>(2.0*half_width, 0.0, 0.0);
	    vertical = vec3<T>(0.0, 2.0*half_height, 0.0);
	    origin = vec3<T>(0.0, 0.0, 0.0);
	}
	ray<T> get_ray(T u, T v) {
	    return ray<T>(origin, lower_left_corner + u*horizontal + v*vertical - origin);
	}

	vec3<T> origin;
	vec3<T> lower_left_corner;
	vec3<T> horizontal;
	vec3<T> vertical;

};

