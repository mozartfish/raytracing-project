/*This class defines a ray object
 *Author: Pranav Rajan
 *Date: May 24, 2019
 */

#ifndef RAYH
#define RAYH

#include "vec3.h"

class ray
{
 public:
  //Empty constructor
  ray()
  {
    
  }

  //Constructor that takes two arguments
  ray(const vec3& a, const vec3& b)
  {
    A = a;
    B = b;
  }

  //Define origin vector
  vec3 origin() const
  {
    return A;
  }

  //Define the direction vector
  vec3 direction() const
  {
    return B;
  }

  //Function that moves a point along a line in 3d space based on the value of t
  vec3 point_at_parameter(float t) const
  {
    return A + t * B;
  }

  //Define A and B as vectors
  vec3 A;
  vec3 B;
};

#endif
