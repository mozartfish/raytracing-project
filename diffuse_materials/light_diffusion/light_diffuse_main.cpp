/*
 *This program draws multiple objects with diffuse shading (matte shading)
 *Author: Pranav Rajan
 *Date: May 27, 2019
 */

#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"

//Define a function for diffusion effect
vec3 random_in_unit_sphere()
{
  vec3 p; // hitpoint vector

  do
  {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
  }
  while (p.squared_length() >= 1.0);

  return p;
}
//Define a color vector function for rendering the scene
vec3 color(const ray& r, hitable *world)
{
  hit_record rec; // define a record of all the hitable objects

  if (world->hit(r, 0.0, MAXFLOAT, rec))
  {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    return 0.5 * color(ray(rec.p, target - rec.p), world);
  }
  else
  {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);

    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main()
{
  //define the x axis
  int nx = 200;

  //define the y-axis
  int ny = 100;

  //define the number of samples
  int ns = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  hitable *list[2]; //define a list of hitable objects

  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  hitable *world = new hitable_list(list, 2); // create a new image world
  camera cam; // define a new camera object

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      vec3 col(0, 0, 0);

      //The sampling calculation
      for (int s = 0; s < ns; s++)
      {
	float u = float(i + drand48()) / float(nx);
	float v = float(j + drand48()) / float(ny);
	ray r = cam.get_ray(u, v);
	vec3 p = r.point_at_parameter(2.0);
	col += color(r, world);
      }

      col /= float(ns); // subdivide the col into subdivisions based on the number of samples
      col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      int ir = int(255.99 * col[0]); // compute the red color
      int ig = int(255.99 * col[1]); // compute the green color
      int ib = int(255.99 * col[2]); // compute the blue color

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  
}
