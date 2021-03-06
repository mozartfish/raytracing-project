/*
 *This class is an abstract class that allows you to draw multiple objects and have rays hit different objects.
 *Author: Pranav Rajan
 * Date: May 27, 2019
 */

#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

//A struct for keeping track of normal vectors, vectors and values t (the value that we use for the ray intersection function)
struct hit_record
{
  float t;
  vec3 p;
  vec3 normal;
};

class hitable
{
 public:
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif
  

  
