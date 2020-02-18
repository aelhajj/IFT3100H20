// IFT3100H20_ImageImport/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetBackgroundColor(31);
  // importer une image située dans ./bin/data
  //image.load("agaragar.jpg");
  imageStruct image;
  image.image.load("agaragar.jpg");
  image.image_origin_x = 0;
  image.image_origin_y = 0;
  image.image_width = 900;
  image.image_heigth = 900;
  images.push_back(image);

  offset_vertical = 32;
  offset_horizontal = 32;
  // redimensionner la fenêtre selon la résolution de l'image
  ofSetWindowShape(screen_width, screen_height);
}

void Renderer::draw()
{
  // afficher l'image sur toute la surface de la fenêtre d'affichage
  for (imageStruct image: images)
  image.image.draw(image.image_origin_x,
                   image.image_origin_y,
                   image.image_width ,
                   image.image_heigth);

  if (is_mouse_button_pressed)
  {
    // dessiner la zone de sélection
    draw_zone(
      mouse_press_x,
      mouse_press_y,
      mouse_current_x,
      mouse_current_y);
  }
  else
  {
    if (!croping_zone.empty())
    {
      draw_zone(
        croping_zone[0],
        croping_zone[1],
        croping_zone[2],
        croping_zone[3]);
    }

  }

  // dessiner le curseur
  //draw_cursor(mouse_current_x, mouse_current_y);

}

void Renderer::draw_zone(float x1, float y1, float x2, float y2) const
{
  float x2_clamp = min(max(0.0f, x2), (float) ofGetWidth());
  float y2_clamp = min(max(0.0f, y2), (float) ofGetHeight());

  ofSetLineWidth(radius);
  ofSetColor(255);
  ofNoFill();
  ofDrawRectangle(x1, y1, x2_clamp - x1, y2_clamp - y1);
  ofFill();
  ofDrawEllipse(x1, y1, radius, radius);
  ofDrawEllipse(x1, y2_clamp, radius, radius);
  ofDrawEllipse(x2_clamp, y1, radius, radius);
  ofDrawEllipse(x2_clamp, y2_clamp, radius, radius);
}

// fonction qui dessine un curseur
// void Renderer::draw_cursor(float x, float y) const
// {
//   float length = 10.0f;
//   float offset = 5.0f;
//
//   ofSetLineWidth(2);
//   ofDrawLine(x + offset, y, x + offset + length, y);
//   ofDrawLine(x - offset, y, x - offset - length, y);
//   ofDrawLine(x, y + offset, x, y + offset + length);
//   ofDrawLine(x, y - offset, x, y - offset - length);
// }
