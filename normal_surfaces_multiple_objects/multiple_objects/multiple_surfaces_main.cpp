/*
 *This program draws multiple objects with shading
 *Author: Pranav Rajan
 *Date: May 27, 2019
 */

#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"

//Define a color vector function for rendering the scene
vec3 color(const ray& r, hitable *world)
{
  hit_record rec;

  if (world->hit(r, 0.0, MAXFLOAT, rec))
  {
    return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
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
  //Define the x-axis
  int nx = 200;

  //Define the y-axis
  int ny = 100;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  //Define the coordinates of the screen view
  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);
  hitable *list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  hitable *world = new hitable_list(list, 2);

  for(int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);

      //Compute the ray
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);

      vec3 p = r.point_at_parameter(2.0);
      vec3 col = color(r, world);

      int ir = int(255.99 * col[0]); // compute the red color
      int ig = int(255.99 * col[1]); // compute the green color
      int ib = int(255.99 * col[2]); // compute the blue color

      std::cout << ir << " " << ig << " " << ib << "\n";
	
    }
  }
}
