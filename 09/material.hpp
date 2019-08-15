#pragma once

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
bool refract(const vec3<T>& v, const vec3<T>& n, float ni_over_nt, vec3<T>& refracted){
	vec3<T> uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
	if (discriminant > 0 ) {
		refracted = ni_over_nt*(uv - n * dt) - n*sqrt(discriminant);
		return true;
	}
	return false;
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
		metal(const vec3<T>& a, T f = (T)0) : albedo(a), fuzzy(f) { if(fuzzy > 1) fuzzy = 1;}
		bool scatter(const ray<T>& r_in,
							 const hit_record<T>& rec,
							 vec3<T>& attenuation,
							 ray<T>& scattered) const {
			vec3<T> reflected = reflect(unit_vector(r_in.direction()), rec.normal);
			scattered = ray<T>(rec.p, reflected + fuzzy*random_in_unit_sphere<T>());
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		};
		vec3<T> albedo;
		T fuzzy;
};

template <typename T>
class dieletric : public material<T> {
	public:
		dieletric(float ri) : ref_idx(ri) {}
		bool scatter(const ray<T>& r_in,
							 const hit_record<T>& rec,
							 vec3<T>& attenuation,
							 ray<T>& scattered) const {

			vec3<T> outward_normal;
			vec3<T> reflected = reflect(r_in.direction(), rec.normal);
			T ni_over_nt = (T)0.0;
			attenuation = vec3<T>(1.0, 1.0, 1.0);
			vec3<T> refracted;
			if(dot(r_in.direction(), rec.normal) > 0) {
				outward_normal = -rec.normal;
				ni_over_nt = ref_idx;
			}
			else {
				outward_normal = rec.normal;
				ni_over_nt = 1.0 / ref_idx;
			}
			if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
				scattered = ray<T>(rec.p, refracted);
			}
			else {
				scattered = ray<T>(rec.p, reflected);
				return false;
			}
			return true;
		}

		T ref_idx;
};

