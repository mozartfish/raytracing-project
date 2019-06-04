/*
 *This class defines a camera for use in anti-aliasing.
 * Anti-Aliasing is a technique used to reduce jitter in an image which is defined as the jagged edges for a picture.
 * By using random sampling such as monte-carlo methods and other kinds of methods, we can figure out a way to blend colors such that we get a smoother shape like when we take photos with a camera
 *Author: Pranav Rajan
 *Date: May 27, 2019
 *Version 1.0
 *
 * Added in an adjustable field of view. Added in a slanted field of view with orthonormal basis (u, v, w). Also added in aperture
 *Author: Pranav Rajan
 * Date: June 4, 2019
 *Version 1.1
 */

#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

// Define a vector for calculating aperture for the camera
vec3 random_in_unit_disk()
{
  vec3 p;
  do
  {
    p = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
  } while (dot(p, p) >= 1.0);

  return p;
}

class camera
{
 public:
  //Constructor
  camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
  {
    lens_radius = aperture / 2;
    float theta = vfov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    origin = lookfrom; // this is where the camera is looking from
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
  }
  

  //Getter function that returns a ray vector
  ray get_ray(float s, float t)
  {
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();

    return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
  }

  //define some vectors corresponding to the image world
  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 u, v, w;
  float lens_radius;
};

#endif
