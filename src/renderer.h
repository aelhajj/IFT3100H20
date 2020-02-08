// IFT3100H20_ImageImport/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include <vector>

class Renderer
{
public:

  ofImage image;
  int image_origin_x = 0;
  int image_origin_y = 0;
  int image_width = 900;
  int image_heigth = 900;

  int offset_vertical;
  int offset_horizontal;

  int mouse_press_x;
  int mouse_press_y;

  int mouse_current_x;
  int mouse_current_y;

  int radius;

  bool is_mouse_button_pressed;

  std::vector<int> croping_zone;

  void setup();
  void draw();

  void reset();

  void draw_zone(float x1, float y1, float x2, float y2) const;
  void draw_cursor(float x, float y) const;

};
