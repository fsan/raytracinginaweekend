#ifndef MATERIALH
#define MATERIALH

#include "vec3.hpp"
#include "hitable.hpp"

template <typename T>
vec3<T> random_in_unit_sphere(){
    vec3<T> p;
    do{
	p = (T)2.0*vec3<T>(drand48(), drand48(), drand48()) - vec3<T>((T)1.0,(T)1.0,(T)1.0);

    }while(p.squared_length() >= 1.0);
    return p;
};

template <typename T>
vec3<T> reflect(const vec3<T>& v, const vec3<T>& n){
	return v - 2*dot<T>(v,n)*n;
}

template <typename T>
class material {
	public:
		virtual bool scatter(const ray<T>& r_in,
							 const hit_record<T>& rec,
							 vec3<T>& attenuation,
							 ray<T>& scattered) const = 0;
};

template <typename T>
class lambertian : public material<T> {
	public:
		lambertian(const vec3<T>& a) : albedo(a) {}
		bool scatter(const ray<T>& r_in,
							 const hit_record<T>& rec,
							 vec3<T>& attenuation,
							 ray<T>& scattered) const {
			vec3<T> target = rec.p + rec.normal + random_in_unit_sphere<T>();
			scattered = ray<T>(rec.p, target - rec.p);
			attenuation = albedo;
			return true;
		};

		vec3<T> albedo;

};

template <typename T>
class metal : public material<T> {
	public:
		metal(const vec3<T>& a) : albedo(a) {}
		bool scatter(const ray<T>& r_in,
							 const hit_record<T>& rec,
							 vec3<T>& attenuation,
							 ray<T>& scattered) const {
			vec3<T> reflected = reflect(unit_vector(r_in.direction()), rec.normal);
			scattered = ray<T>(rec.p, reflected);
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		};
		vec3<T> albedo;
};

#endif
