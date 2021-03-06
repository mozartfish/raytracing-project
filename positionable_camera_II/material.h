/*
 *This is an abstract class that tells how the rays will interact with the surface. These interactions include lambertian (diffuse) shading, reflection etc. 
 *Author: Pranav Rajan
 *Date May 28, 2019
 *Version 1.0
 *
 *Added in fuzz
 *Author: Pranav Rajan
 *Date: May 28, 2019
 *Version 1.1
 *
 *Added in refraction for use with dielectrics
 *Author: Pranav Rajan
 *Date: June 3, 2019
 *Version: 1.2
 *
 *Added in the Schlick Polynomial (used for approximating Fresnel Equation)
 * for reflection and refraction for creating glass and other surfaces involving
 * reflection and refraction
 * Date: June 4, 2019
 * Version 1.3
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

//Function for computing refraction
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
  vec3 uv = unit_vector(v);
  float dt = dot(uv, n);
  float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);

  if (discriminant > 0)
  {
    refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
    return true;
  }
  else
  {
    return false;
  }
}

// Function for computing the Schlick Polynomial which is a substitute for
// Fresnel's Equation for reflection and refraction
float schlick(float cosine, float ref_idx)
{
  float r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0 * r0;

  return r0 + (1 - r0) * pow((1 - cosine), 5);
}


//Define dielectric effect
class dielectric : public material
{
 public:
  dielectric(float ri) : ref_idx(ri)
  {
  }

  //Scatter function that can be overriden by other classes or things that inherit from dielectrics
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
  {
    vec3 outward_normal; // the outward normal vector
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ni_over_nt;
    attenuation = vec3(1.0 ,1.0 ,1.0);
    vec3 refracted;
    float reflect_prob; // variable to store reflection probability for sampling
    float cosine;

    if (dot(r_in.direction(), rec.normal) > 0)
    {
      outward_normal = -rec.normal;
      ni_over_nt = ref_idx;
      cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    else
    {
      outward_normal = rec.normal;
      ni_over_nt = 1.0 / ref_idx;
      cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
    {
      reflect_prob = schlick(cosine, ref_idx);
    }
    else
    {
      scattered = ray(rec.p, reflected);
      reflect_prob = 1.0;
    }
    if (drand48() < reflect_prob)
    {
      scattered = ray(rec.p, reflected);
    }
    else
    {
      scattered = ray(rec.p, refracted);
    }

    return true;
  }
  
  float ref_idx; // a vector for the refraction index for snell's law
};

//Define metallic effect
class metal : public material
{
 public:
  //Constructor with fuzz
  metal(const vec3& a, float f) : albedo(a)
  {
    if (f < 1)
    {
      fuzz = f;
    }
    else
    {
      fuzz = 1;
    }
  }

  //Define the scatter function for metallic effect
  virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
  {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;

    return (dot(scattered.direction(), rec.normal) > 0);
  }

  vec3 albedo; // define the albedo vector
  float fuzz; // define fuzz 
  
};

#endif
