/*
 * Hello World in computer graphics
 * Author: Pranav Rajan
 * Date: May 24, 2019
 */

#include <iostream>
#include "vec3.h"

using namespace std;

int main()
{
  int nx = 200; // the x coordinate axis
  int ny = 100; // the y coordinate axis

  cout << "P3\n" << nx << " " << ny << "\n255\n";

  for (int j = ny - 1; j >= 0; j--)
  {
    for (int i = 0; i < nx; i++)
    {
      vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);

      int ir = int(255.99 * col[0]); // compute the red color
      int ig = int(255.99 * col[1]); // compute the green color
      int ib = int(255.99 * col[2]); // compute the blue color

      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
