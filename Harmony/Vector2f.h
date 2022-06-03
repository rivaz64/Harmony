/**
 * @file oaVector2f.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include <cmath>

namespace Harmony {
/**
 * @brief bidimencional vector of floats
*/
class Vector2f
{
 public:
  /**
   * @brief default constructor for the vector2f
  */
  Vector2f() = default;

  /**
   * @brief constructor with parameters
   * @param _x
   * @param _y
  */
  Vector2f(float _x, float _y) :x(_x), y(_y) {}

  ~Vector2f() = default;

  /**
   * @brief compares if two vectors are equal
   * @param v 
   * @return 
  */

  inline bool const
  operator==(const Vector2f& v) const {
    return x == v.x && y == v.y;
  }

  /**
  * @brief adds the vector v and this one
   * @param v
   * @return
  */
  inline Vector2f const
  operator+(const Vector2f& v) const {
    return { x + v.x , y + v.y };
  }

  /**
  * @brief adds the float v and this one
   * @param v
   * @return
  */
  inline Vector2f const
  operator+(float v) const {
    return { x + v , y + v };
  }

  /**
   * @brief adds the vector v to this one
   * @param v
  */
  inline Vector2f&
  operator+=(const Vector2f& v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  /**
   * @brief this vector minus vector v
   * @param v
   * @return
  */
  inline Vector2f const
  operator-(const Vector2f& v) const {
    return { x - v.x , y - v.y };
  }

  /**
  * @brief minus the float v and this one
   * @param v
   * @return
  */
  inline Vector2f const
  operator-(float v) const {
    return { x - v , y - v };
  }

  /**
   * @brief substract vector v from this
   * @param v
  */
  inline Vector2f&
  operator-=(const Vector2f& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  /**
   * @brief calculates a vector with the same direction as this and a lenght multiplied by v
   * @param v
   * @return
  */
  inline Vector2f const
  operator*(float v) const {
    return { x * v , y * v };
  }

  /**
   * @brief multiply the length vector the vector by v
   * @param v
  */

  inline Vector2f&
  operator*=(float v) {
    x *= v;
    y *= v;
    return *this;
  }

  /**
   * @brief calculates a vector with the same direction as this and a lenght divided by v
   * @param v
   * @return
  */
  inline Vector2f const
  operator/(float v) const {
    v = 1.f / v;
    return { x * v , y * v };
  }

  /**
   * @brief divide the length vector the vector by v
   * @param v
  */
  inline Vector2f&
  operator/=(float v) {
    v = 1.f / v;
    x *= v;
    y *= v;
    return *this;
  }

  /**
   * @brief multiplies each parameter for its congruent in the other vector
   * @param v 
   * @return 
  */
  inline Vector2f
  operator*(const Vector2f& v) {
    return { x * v.x,y * v.y };
  }

  /**
   * @brief the lenght of the vector
   * @return
  */
  inline float const
  magnitud() const {
    return std::sqrt(x * x + y * y);
  }

  /**
   * @brief the unitary form of the vector
   * @return
  */
  inline Vector2f const
  normalized() const {
    auto lenght = magnitud();
    if(lenght<.001){
     return Vector2f(0,0);
    }
    return *this / lenght;
  }

  /**
  * @brief makes this vector have a magnitud of 1
  * @return
  */
  inline void
  normalize() {
    *this  /= sqrt(x * x + y * y);
  }

  /**
   * @brief proyects this vector into v
   * @param v
   * @return
  */
  inline Vector2f const
  project(const Vector2f& v) const {
    return v * (dot(*this,v) / dot(v,v));
  }

  /**
   * @brief the direction in radians of the vector
   * @return
  */
  inline float const
  getDirection() const {
    return atan2(x, y);
  }

  /**
   * @brief changes the direction of the vector to r in radians and the lenght stays the same
   * @return
  */
  inline void 
  setDirection(float r) {
    float l = magnitud();
    x = l * cos(r);
    y = l * sin(r);
  }

  /**
   * @brief dot product of two vectors
   * @param v1
   * @param v2
   * @return
  */
  inline static float
  dot(const Vector2f& v1, const Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
  }

  /**
   * @brief cross product of two vectors
   * @param v1
   * @param v2
   * @return
  */
  inline static float
  cross(const Vector2f& v1, const Vector2f& v2) {
    return static_cast<double>(v1.x) * static_cast<double>(v2.y)
         - static_cast<double>(v1.y) * static_cast<double>(v2.x);
  }

  /**
   * @brief calculates the intersection of to lines
   * @param v1 start line 1
   * @param v2 end line 1
   * @param v3 start line 2
   * @param v4 end line 2
   * @param out intersection
   * @return if they intersect
  */
  inline static bool
  intersect(Vector2f v1,
    Vector2f v2,
    Vector2f v3,
    Vector2f v4,
    Vector2f& out)
  {
    //http://mathworld.wolfram.com/Line-LineIntersection.html

    auto detL1 = cross(v1,v2);
    auto detL2 = cross(v3,v4);
    auto m12 = v1-v2;
    auto m34 = v3-v4;

    float xnom = cross(Vector2f(detL1, m12.x), Vector2f(detL2, m34.x));
    float ynom = cross(Vector2f(detL1, m12.y), Vector2f(detL2, m34.y));
    float denom = cross(m12,m34);

    if(denom == 0.0)//Lines don't seem to cross
    {
        out.x = NAN;
        out.y = NAN;
        return false;
    }

    out.x = xnom / denom;   
    out.y = ynom / denom;

    auto LineLen = (v2-v1).magnitud();

    if((out-v1).magnitud()<LineLen && (out-v2).magnitud()<LineLen){
      return true;
    }

    return false;
  }

 public:

  static const Vector2f ZERO;

  /**
   * @brief the x component of the vector
  */
  float x;

  /**
   * @brief the y component of the vector
  */
  float y;

};


}
