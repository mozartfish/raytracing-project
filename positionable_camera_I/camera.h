/*
 *This class defines a camera for use in anti-aliasing.
 * Anti-Aliasing is a technique used to reduce jitter in an image which is defined as the jagged edges for a picture.
 * By using random sampling such as monte-carlo methods and other kinds of methods, we can figure out a way to blend colors such that we get a smoother shape like when we take photos with a camera
 *Author: Pranav Rajan
 *Date: May 27, 2019
 *
 * Added in an adjustable field of view
 *Author: Pranav Rajan
 * Date: June 4, 2019
 */

#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera
{
 public:
  //Constructor
  camera(float vfov, float aspect)
  {
    float theta = vfov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    lower_left_corner = vec3(-half_width, -half_height, -1.0);
    horizontal = vec3(2 * half_width, 0.0, 0.0);
    vertical = vec3(0.0, 2 * half_width, 0.0);
    origin = vec3(0.0, 0.0, 0.0);
  }
  

  //Getter function that returns a ray vector
  ray get_ray(float u, float v)
  {
    return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
  }

  //define some vectors corresponding to the image world
  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
};

#endif
