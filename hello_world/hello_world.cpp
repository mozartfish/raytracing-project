/*
 *The equivalent of hello world in computer graphics.
 *Author: Pranav Rajan
 *Date: May 9, 2019
 */

#include<iostream>
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
      float r = float(i) / float(nx); // compute the red color
      float g = float(j) / float(ny); // compute the green color
      float b = 0.2; // compute the blue color

      int ir = int(255.99 * r); // scale the r value to fit coordinate system
      int ig = int(255.99 * g); // scale the g value to fit coordinate system
      int ib = int(255.99 * b); // scale the g value to fit coordinate system
      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
