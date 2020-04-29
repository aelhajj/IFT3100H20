#include "raytracer.h"
#include <string>
#include <cstdlib>

void Raytracer::setup()
{
  image->position_x = 300;
  image->position_y = 200;
  image->width = 512;
  image->height = 512;
  image->image.load("image512x512.ppm");
}
void Raytracer::draw()
{
  image->draw();
}
