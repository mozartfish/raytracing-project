/*
 *This is an abstract class that tells how the rays will interact with the surface. These interactions include lambertian (diffuse) shading, reflection etc. 
 *Author: Pranav Rajan
 *Date May 28, 2019
 */

#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "hitable.h"

struct hit_record;

//Define the material class with a function that can be overriden by other classes that inherit from it
class material
{
 public:
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

//Definition for a random unit sphere
vec3 random_in_unit_sphere()
{
  vec3 p;
  do
  {
    p = 2.0*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
  } while (p.squared_length() >= 1.0);
    
  return p;
}

//Class that inherits from material and implements diffusion shading
class lambertian : public material {
 public:
  //Empty constructor
  lambertian(const vec3& a) : albedo(a)
  {
  }

  //Override the scatter function for lambertian (diffusion shading)
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
  {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = ray(rec.p, target-rec.p);
    attenuation = albedo;
    
    return true;
  }

  vec3 albedo; //define the albedo vector
};

//Function for computing reflection
vec3 reflect(const vec3& v, const vec3& n)
{
  return v - 2 * dot(v, n) * n;
}

//Define metallic effect
class metal : public material
{
 public:
  //Empty constructor
  metal(const vec3& a) : albedo(a)
  {
  }

  //Define the scatter function for metallic effect
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
  {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
  }

  vec3 albedo; // define the albedo vector
  
};

#endif
