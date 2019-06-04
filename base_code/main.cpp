/*
 *This program draws multiple objects with metallic shading, reflections etc.
 *Author: Pranav Rajan
 *Date: May 28, 2019
 *
 *Rewrote the entire main to render a scene with multiple spheres and effects including dielectrics, shading, reflection, refraction, glass, etc. 
 *Author: Pranav Rajan
 *Date June 4, 2019
 */

#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"

//Define a color vector function for rendering the scene
vec3 color(const ray& r, hitable *world, int depth)
{
  hit_record rec; // new hit record object

  if (world->hit(r, 0.001, MAXFLOAT, rec))
  {
    ray scattered; 
    vec3 attenuation;

    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
    {
      return attenuation * color(scattered, world, depth + 1);
    }
    else
    {
      return vec3(0, 0, 0);
    }
  }
  else
  {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);

    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

//Define a function that will draw the objects for the scene
hitable *random_scene()
{
  int n = 500;
  hitable **list = new hitable*[n + 1];
  list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
  int i = 1;

  for (int a = -11; a < 11; a++)
  {
    for (int b = -11; b < 11; b++)
    {
      float choose_mat = drand48();
      vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
      if ((center-vec3(4, 0.2, 0)).length() > 0.9)
      {
	if (choose_mat < 0.8) // for diffusion
	{
	  list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
	}
	else if (choose_mat < 0.95) // for metallic material
	{
	  list[i++] = new sphere(center, 0.2, new metal(vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 1.0));
	}
	else // for glass material
	{
	  list[i++] = new sphere(center, 0.2, new dielectric(1.5));
	}
      }
    }
  }

  list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
  list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
  list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

  return new hitable_list(list, i);
  
}


int main()
{
  //define the x axis
  int nx = 1200;

  //define the y-axis
  int ny = 800;

  //define the number of samples
  int ns = 10;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  hitable *list[5]; // define the number of hitable objects
  float R = cos(M_PI / 4); //constant for the aperture for the camera

  list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
  list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
  list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
  list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
  list[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));
  
  hitable *world = new hitable_list(list,5); // create image world
  world = random_scene();
  
  //Define some variables for aperture and camera features
  vec3 lookfrom(13, 2, 3); // Where the camera is looking from
  vec3 lookat(0, 0, 0); // Where the person is looking from
  float dist_to_focus = 10.0; // distance between the lens and the sensor for an actual camera (simulated here(
  float aperture = 0.1; // value for camera aperture

  camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus); // create a new camera object

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
	col += color(r, world, 0);
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
