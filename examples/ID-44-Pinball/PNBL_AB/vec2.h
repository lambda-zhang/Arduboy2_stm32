#ifndef _VEC2_ 
#define _VEC2_ 

#include <math.h>

struct vec2;
vec2 operator*(vec2 lhs, const float &rhs);
vec2 operator/(vec2 lhs, const float &rhs);

struct vec2
{
  float x;
  float y;

  vec2() : x(0), y(0) {}
  vec2(float vx, float vy) : x(vx), y(vy) {}
  vec2(const vec2 &copy) : x(copy.x), y(copy.y) {}

  float getMagnitude()
  {
    float fpout = sqrt(abs(pow(x, 2) + pow(y, 2)));
    //Serial.print("magnitude: ");
    //Serial.println(fpout.getValue());
    return fpout;
  }

  vec2 getNormal()
  {
    if (getMagnitude() == 0.0)
      return vec2(0, 1);
    return (vec2(x, y) / getMagnitude());
  }

  void convertNormal()
  {
    float mag = getMagnitude();
    if (mag == 0.0) {
      x = 0;
      y = 0;
    }
    else {
      x = x / mag;
      y = y / mag;
    }
  }

  vec2 &operator+=(const vec2 &rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  
  vec2 &operator-=(const vec2 &rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  vec2 &operator*=(const float &rhs)
  {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  vec2 &operator/=(const float &rhs)
  {
    x *= rhs;
    y *= rhs;
    return *this;
  }

  boolean operator>(const vec2 &rhs) {
    return (x > rhs.x && y > rhs.y);
  }

  boolean operator<(const vec2 &rhs) {
    return (x < rhs.x && y < rhs.y);
  }

  boolean operator==(const vec2 &rhs) {
    return (x == rhs.x && y == rhs.y);
  }
  
  boolean operator!=(const vec2 &rhs) {
    return !(*this == rhs);
  }

  /*vec2 &operator=(const vec2 &rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }*/

  //debug
  void print() {
    Serial.print("vec2: ");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
  }

};

vec2 operator+(vec2 lhs, const vec2 &rhs)
{
  //vec2 t = lhs;
  //t += rhs;
  return (lhs += rhs);
}

vec2 operator-(vec2 lhs, const vec2 &rhs)
{
  //vec2 t = lhs;
  //t -= rhs;
  return (lhs -= rhs);
}

// dot product
float operator*(vec2 lhs, const vec2 &rhs)
{
  lhs.x *= rhs.x;
  lhs.y *= rhs.y;
  return (lhs.x + lhs.y);
}

// constant multiple
vec2 operator*(vec2 lhs, const float &rhs)
{
  lhs.x *= rhs;
  lhs.y *= rhs;
  return lhs;
}

// constant divide
vec2 operator/(vec2 lhs, const float &rhs)
{
  lhs.x /= rhs;
  lhs.y /= rhs;
  return lhs;
}

/*vec2 operator<<(vec2 lhs, const int &rhs)
{
  lhs.x <<= rhs;
  lhs.y <<= rhs;
  return lhs;
}

vec2 operator>>(vec2 lhs, const int &rhs)
{
  lhs.x >>= rhs;
  lhs.y >>= rhs;
  return lhs;
}*/

#endif
