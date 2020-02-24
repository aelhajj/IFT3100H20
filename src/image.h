#pragma once

#include "ofMain.h"
#include <vector>
#include "sceneObject.h"



class ImageStruct : public SceneObject
{
public:
  ofImage image;
  int image_origin_x = 0;
  int image_origin_y = 0;
  int image_width = 900;
  int image_heigth = 900;
  int image_rotation = 0;
  float scale = 1;


  void translate(int x, int y)
  {
    image_origin_x += x;
    image_origin_y += y;
  }

  void zoomIn()
  {
    scale += 0.25;
  }

  void zoomOut()
  {
    if (scale > 0.25)
      scale -= 0.25;
  }

  void rotate()
  {
    image_rotation += 5;
  }

  void draw()
  {
    image.draw(image_origin_x,
               image_origin_y,
               image_width ,
               image_heigth);
  }

};
