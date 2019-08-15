#pragma once

#include "ray.hpp"

template <class T>
class material;

template <typename T>
struct hit_record {
	T t;
	vec3<T> p;
	vec3<T> normal;
	material<T>* mat_ptr;
};

template <typename T>
class hitable {
	public:
		virtual bool hit(const ray<T>& r, T t_min, float t_max, hit_record<T>& rec) const = 0;
};

