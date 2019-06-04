/*
 *This class defines a class for hitable objects for rendering a scene. The class allows for multiple objects such as spheres, planes, cylinders etc.
 *Author: Pranav Rajan
 *Date: May 27, 2019
 */

#ifndef HITABLE_LISTH
#define HITABLE_LISTH

#include "hitable.h"

class hitable_list: public hitable
{
 public:
  //Empty constructor
  hitable_list()
  {
  }

  //Constructor that takes two arguments
  hitable_list(hitable **l, int n)
  {
    list = l;
    list_size = n;
  }

  //Define a hit function that can be overridden for different objects
  virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

  //Pointer to a hitable list
  hitable **list;

  int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;

  for(int i = 0; i < list_size; i++)
  {
    if (list[i] -> hit(r, t_min, closest_so_far, temp_rec))
    {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}

#endif
