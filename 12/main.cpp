#include <iostream>
#include <math.h>
#include <float.h>
#include <random>

#include "material.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "hitable_list.hpp"
#include "common.hpp"

#ifndef QUALITY
#define QUALITY 2
#endif

#ifndef BOUNCES
#define BOUNCES 50
#endif

#ifndef FACTOR 
#define FACTOR 4 
#endif

vec3<float> color(ray<float>& r, hitable<float> *world, int depth){
	hit_record<float> rec;
	if (world->hit(r, 0.001, MAXFLOAT,rec)) {
		ray<float> scattered;
		vec3<float> attenuation;

		if(depth < BOUNCES && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
			
			return attenuation*color(scattered, world, depth+1);
		}
		else {
			return vec3<float>(0.0, 0.0, 0.0);
		}
	}
	else {
		vec3<float> unit_direction = unit_vector(r.direction());
		float t = 0.5 *(unit_direction.y() + 1.0);
		return (float)(1.0-t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5,0.7,1.0);
	}
}

hitable<float>* random_scene(int n){
    int i = 0;
    hitable<float> **list = new hitable<float>*[n+1];
	auto diemat = new lambertian<float>(vec3<float>(0.8,0.3,0.3));
	auto ground = new lambertian<float>(vec3<float>(0.5,0.5,0.51));

	auto metalmat = new metal<float>(vec3<float>(0.8,0.6,0.2), 0.2);
	auto mat4 = new dieletric<float>(1.3);
	auto mat5 = new dieletric<float>(0.51);

	list[i++] = new sphere<float>(vec3<float>(0,-1000.5,0), 1000.0, ground);

	list[i++] = new sphere<float>(vec3<float>(+0,1.5,0), 3, metalmat);
	list[i++] = new sphere<float>(vec3<float>(+4,1.5,0), 3, mat4);
	list[i++] = new sphere<float>(vec3<float>(+4,1.5,0), -2.98, mat5);
	list[i++] = new sphere<float>(vec3<float>(-4,1.5,0), 3, diemat);

	for(;i<6; i++){
	    std::cerr << i << "\n";
	    list[i++] = new sphere<float>(vec3<float>(drand48(), 1.5, drand48()),
					    3, 
					    new lambertian<float>(vec3<float>(0.5,0.5,0.5))
					);
	}

    return new hitable_list<float>(list, n);
}


int main(){
	const int factor = FACTOR;
	const int nx = 200 * factor;
	const int ny = 100 * factor;
	const float fnx = (float)nx;
	const float fny = (float)ny;
	const int ns = QUALITY * factor * 8 ;
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	hitable<float> *list[5];


	//float R = cos(M_PI/4);


	hitable<float> *world = random_scene(10);

	vec3<float> lookfrom = vec3<float>(-5.8,10.6,-2.8);
	vec3<float> lookat = vec3<float>(0,0,0);
	camera<float> cam(lookfrom,             // lookfrom
			  lookat,               //lookat
			  vec3<float>(0,1,0),   //view-up
			  90,                   //vfov
			  float(nx)/float(ny),  //aspect
			  0.3,                  //aperture
			  (lookfrom-lookat).length() //dist_to_focus
		     );

	srand(time(0));
	for(int j = ny-1 ; j > 0 ; j--){
		for(int i = 0; i < nx; i++) {
			vec3<float> col(0,0,0);

				// this could be better if not setting atomic write
				// it could an buffer array for each thread and then a reduction
				// maybe it's faster
				// but it would some work which I'm not going into it
				#pragma num_threads(6)
				#pragma omp parallel for schedule(dynamic)
				for(int s = 0; s < ns; s++) {
					auto u = float(i + fRand()) / fnx;
					auto v = float(j + fRand()) / fny;

					ray<float> r = cam.get_ray(u,v);
                                        #pragma atomic write
					col += color(r, world,0);
				}
			col /= float(ns);

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);


			std::cout << ir << " " << ig << " " << ib << "\n";
		}
                //#pragma omp barrier
		float stat = (float)(-j+ny)/(float)ny ;
		std::cerr << (ny-j) << " " << stat << '\r';
	}
	return 0 ;
}
