#ifndef MATERIALH
#define MATERIALH

#include "hitable_list.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class material{
    public:
	virtual bool scatter(const ray<T>& r_in,
			     const hit_record<T>& rec,
			     vec<T>& attenuation,
			     ray<T>& scattered) const = 0;
};

#endif MATERIALH
