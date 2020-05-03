#pragma once

#include "ofMain.h"
#include <vector>
#include <math.h>

// énumération de types de courbe
enum class CurveType {bezier_quadratic, bezier_cubic, bezier_surface};

inline int factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

inline void bezier_surface(
  float animation_float,
  float u, float v,
  std::vector<std::vector<float>>& ctrl_pointx,
  std::vector<std::vector<float>>& ctrl_pointy,
  std::vector<std::vector<float>>& ctrl_pointz,
  float&  x,  float& y, float&  z)
  {
    animation_float = -animation_float;
    x = 0; y = 0; z = 0;
    int m = ctrl_pointx.size();
    int n = ctrl_pointx[0].size();
    for (int i = 0; i < ctrl_pointx.size(); i++)
    {
      animation_float = - animation_float;
      for (int j = 0; j < ctrl_pointx[i].size(); j++)
      {
        x += (factorial(n)/(factorial(i) * factorial(n - i))) * (pow(u, i) * pow(1 - u, n - i) * (factorial(m)/(factorial(j) * factorial(m - j)))) * (pow(v, j) * pow(1 - v, m - j)) * (ctrl_pointx[i][j] + animation_float);
        y += (factorial(n)/(factorial(i) * factorial(n - i))) * (pow(u, i) * pow(1 - u, n - i) * (factorial(m)/(factorial(j) * factorial(m - j)))) * (pow(v, j) * pow(1 - v, m - j)) * (ctrl_pointy[i][j] + animation_float);
        z += (factorial(n)/(factorial(i) * factorial(n - i))) * (pow(u, i) * pow(1 - u, n - i) * (factorial(m)/(factorial(j) * factorial(m - j)))) * (pow(v, j) * pow(1 - v, m - j)) * (ctrl_pointz[i][j] + animation_float);
      }
    }
  }
// fonction d'évaluation d'une courbe de Bézier quadratique (3 points de contrôle)
inline void bezier_quadratic(
  float t,
  float p1x, float p1y, float p1z,
  float p2x, float p2y, float p2z,
  float p3x, float p3y, float p3z,
  float&  x,  float& y, float&  z)
{
  float u = 1 - t;

  x = u * (u * p1x + t * p2x) + t * (u * p2x + t * p3x);
  y = u * (u * p1y + t * p2y) + t * (u * p2y + t * p3y);
  z = u * (u * p1z + t * p2z) + t * (u * p2z + t * p3z);
}

// fonction d'évaluation d'une courbe de Bézier cubique (4 points de contrôle)
inline void bezier_cubic(
  float t,
  float p1x, float p1y, float p1z,
  float p2x, float p2y, float p2z,
  float p3x, float p3y, float p3z,
  float p4x, float p4y, float p4z,
  float&  x,  float& y, float&  z)
{
  float u = 1 - t;
  float uu = u * u;
  float uuu = uu * u;
  float tt = t * t;
  float ttt = tt * t;

  x = uuu * p1x + 3 * uu * t * p2x + 3 * u * tt * p3x + ttt * p4x;
  y = uuu * p1y + 3 * uu * t * p2y + 3 * u * tt * p3y + ttt * p4y;
  z = uuu * p1z + 3 * uu * t * p2z + 3 * u * tt * p3z + ttt * p4z;
}

class Parametric
{
public:
  float animation_float = 1;
  int counter = 1;
  CurveType curve_id;

  string curve_name;

  ofPolyline line_renderer;

  ofVec3f* selected_ctrl_point;
  float* selected_ctrl_pointx;
  float* selected_ctrl_pointy;

  ofVec3f ctrl_point1;
  ofVec3f ctrl_point2;
  ofVec3f ctrl_point3;
  ofVec3f ctrl_point4;

  ofVec3f initial_position1;
  ofVec3f initial_position2;
  ofVec3f initial_position3;
  ofVec3f initial_position4;
  ofVec3f initial_position5;
  ofVec3f initial_position6;
  ofVec3f initial_position7;
  ofVec3f initial_position8;
  ofVec3f initial_position9;
  ofVec3f initial_position10;
  ofVec3f initial_position11;

  ofVec3f position;

  float line_width_outline;
  float line_width_curve;

  float radius;
  float scale;
  float smooth;
  float offset;

  float delta_x;
  float delta_y;

  float motion_speed;

  int framebuffer_width;
  int framebuffer_height;

  int line_resolution;

  int index;

  std::vector<std::vector<float>> ctrl_pointx;
  std::vector<std::vector<float>> ctrl_pointy;
  std::vector<std::vector<float>> ctrl_pointz;

  void setup();
  void update();
  void draw();
  void reset();
  void updateFloatAnimation();
};
