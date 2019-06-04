/*
 *This class defines a sphere object
 *Author: Pranav Rajan
 *Date: May 27, 2019
 * Version 1.0
 *
 *Class updated to account for different kinds of materials
 *Author: Pranav Rajan
 *Date May 28, 2019
 *Version 1.1
 */

#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable
{
 public:
  //Empty constructor
  sphere()
  {
  }

  //Constructor that takes multiple arguments
  sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m)
  {
  };

  //Define a virtual function that can be overriden
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
  vec3 center;
  float radius;
  material *mat_ptr;
};

//Define the hit function for the sphere
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - a * c;

  if (discriminant > 0)
  {
    float temp = (-b - sqrt(discriminant)) / a;
    
    if (temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat_ptr = mat_ptr;

      return true;
    }

    temp = (-b + sqrt(discriminant)) / a;

    if (temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat_ptr = mat_ptr;

      return true;
    }
  }

  return false;
}

#endif
