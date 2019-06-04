/*
 *This class defines a camera for use in anti-aliasing.
 * Anti-Aliasing is a technique used to reduce jitter in an image which is defined as the jagged edges for a picture.
 * By using random sampling such as monte-carlo methods and other kinds of methods, we can figure out a way to blend colors such that we get a smoother shape like when we take photos with a camera
 *Author: Pranav Rajan
 *Date: May 27, 2019
 *Version 1.0
 *
 * Added in an adjustable field of view. Added in a slanted field of view with orthonormal basis (u, v, w)
 *Author: Pranav Rajan
 * Date: June 4, 2019
 *Version 1.1
 */

#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera
{
 public:
  //Constructor
  camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect)
  {
    vec3 u, v, w; // define vectors for the orthonormal basis
    float theta = vfov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    origin = lookfrom; // this is where the camera is looking from
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);
    lower_left_corner = vec3(-half_width, -half_height, -1.0);
    lower_left_corner = origin - half_width * u - half_height * v - w;
    horizontal = 2 * half_width * u;
    vertical = 2 * half_height * v;
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
