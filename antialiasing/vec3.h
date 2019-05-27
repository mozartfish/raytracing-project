/*
 *This class defines colors, directions, offsets, etc for the ray tracer
 *Author: Pranav Rajan
 *Date: May 24, 2019
 */

#ifndef VEC3
#define VEC3

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3  {

    
 public:
  //Empty Constructor
  vec3()
  {
  }

  //Constructor that takes 3 arguments 
  vec3(float e0, float e1, float e2)
  {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
  }

  //Getter methods that return x, y, z coordinates
  inline float x() const
  {
    return e[0];
  }
  inline float y() const
  {
    return e[1];
  }
  inline float z() const
  {
    return e[2];
  }

  //Getter methods that return r, g, b values
  inline float r() const
  {
    return e[0];
  }
  inline float g() const
  {
    return e[1];
  }
  inline float b() const
  {
    return e[2];
  }

  //Methods that define positive and negative vectors
  inline const vec3& operator+() const
  {
    return *this;
  }
  inline vec3 operator-() const
  {
    return vec3(-e[0], -e[1], -e[2]);
  }

  //Methods that return a value corresponding to a particular vector component located in a particular index
  inline float operator[](int i) const
  {
    return e[i];
  }
  inline float& operator[](int i)
  {
    return e[i];
  };

  //Methods that define vector operations
  inline vec3& operator+=(const vec3 &v2);
  inline vec3& operator-=(const vec3 &v2);
  inline vec3& operator*=(const vec3 &v2);
  inline vec3& operator/=(const vec3 &v2);

  //Methods that define vector scalar operations
  inline vec3& operator*=(const float t);
  inline vec3& operator/=(const float t);

  //Method that computes vector length
  inline float length() const
  {
    return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
  }

  //Method that computes the square vector length
  inline float squared_length() const
  {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
  }

  //Method declaration for making unit vector
  inline void make_unit_vector();
    
  float e[3]; //Value for vector operations potentially involving four coordinates
};

//Methods for input and output
inline std::istream& operator>>(std::istream &is, vec3 &t)
{
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}
inline std::ostream& operator<<(std::ostream &os, const vec3 &t)
{
  os << t.e[0] << " " << t.e[1] << " " << t.e[2];
  return os;
}

//Method definition for unit vectors
inline void vec3::make_unit_vector()
{
  float k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
  e[0] *= k; e[1] *= k; e[2] *= k;
}

//Method definition for vector addition
inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

//Method definition for vector subtraction
inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

//Method definition for vector multiplication
inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

//Method definition for vector division
inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

//Method definition for vector scalar multiplication
inline vec3 operator*(float t, const vec3 &v)
{
  return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

//Method definition for vector scalar division
inline vec3 operator/(vec3 v, float t) {
  return vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

//Method definition for vector scalar multiplication
inline vec3 operator*(const vec3 &v, float t) {
  return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

//Method definition for vector dot product
inline float dot(const vec3 &v1, const vec3 &v2) {
  return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];
}

//Method definition for vector cross product
inline vec3 cross(const vec3 &v1, const vec3 &v2) {
  return vec3( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
	       (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
	       (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));
}

//Method definition for vector addition
inline vec3& vec3::operator+=(const vec3 &v){
  e[0]  += v.e[0];
  e[1]  += v.e[1];
  e[2]  += v.e[2];
  return *this;
}

//Method definition for vector multiplication
inline vec3& vec3::operator*=(const vec3 &v){
  e[0]  *= v.e[0];
  e[1]  *= v.e[1];
  e[2]  *= v.e[2];
  return *this;
}

//Method definition for vector division
inline vec3& vec3::operator/=(const vec3 &v){
  e[0]  /= v.e[0];
  e[1]  /= v.e[1];
  e[2]  /= v.e[2];
  return *this;
}

//Method for vector subtraction
inline vec3& vec3::operator-=(const vec3& v) {
  e[0]  -= v.e[0];
  e[1]  -= v.e[1];
  e[2]  -= v.e[2];
  return *this;
}

//Method definition for vector scalar multiplication
inline vec3& vec3::operator*=(const float t) {
  e[0]  *= t;
  e[1]  *= t;
  e[2]  *= t;
  return *this;
}

//Method definition for vector scalar division
inline vec3& vec3::operator/=(const float t) {
  float k = 1.0/t;
    
  e[0]  *= k;
  e[1]  *= k;
  e[2]  *= k;
  return *this;
}

//Method definition for unit vector
inline vec3 unit_vector(vec3 v) {
  return v / v.length();
}

#endif
