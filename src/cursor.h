
#pragma once
#include "renderer.h"
class Cursor
{
public:
  virtual void onMouseMoved(int x, int y) = 0;
  virtual void onMouseDragged(int x, int y) = 0;
  virtual void onMousePressed(int x, int y) = 0;
  virtual void onMouseReleased(int x, int y) = 0;
  virtual void drawCursor() = 0;
};



class CropCursor : public Cursor
{
public:
    CropCursor (Renderer* r)
    {
      renderer = r;
    }
   void onMouseMoved(int x, int y)
   {
     renderer->mouse_current_x = x;
     renderer->mouse_current_y = y;
   }
   void onMouseDragged(int x, int y)
   {
     renderer->mouse_current_x = x;
     renderer->mouse_current_y = y;
   }
   void onMousePressed(int x, int y)
   {

     renderer->is_mouse_button_pressed = true;
     renderer->croping_zone.clear();

     renderer->mouse_current_x = x;
     renderer->mouse_current_y = y;

     renderer->mouse_press_x = x;
     renderer->mouse_press_y = y;
   }
   void onMouseReleased(int x, int y)
   {
     renderer->is_mouse_button_pressed = false;
     if(y > 100)
     {
       renderer->croping_zone.push_back(renderer->mouse_press_x);
       renderer->croping_zone.push_back(renderer->mouse_press_y);
       renderer->croping_zone.push_back(renderer->mouse_current_x);
       renderer->croping_zone.push_back(renderer->mouse_current_y);
     }

     renderer->mouse_current_x = x;
     renderer->mouse_current_y = y;
   }
   void drawCursor()
   {
     float x = renderer->mouse_current_x;
     float y = renderer->mouse_current_y;
     float length = 10.0f;
     float offset = 5.0f;

     ofSetLineWidth(2);
     ofDrawLine(x + offset, y, x + offset + length, y);
     ofDrawLine(x - offset, y, x - offset - length, y);
     ofDrawLine(x, y + offset, x, y + offset + length);
     ofDrawLine(x, y - offset, x, y - offset - length);
   }

 private:
   Renderer* renderer;
};

class NormalCursor : public Cursor
{
public:
    NormalCursor(Renderer* r)
    {
      renderer = r;
      image.load("handCursor.png");
    }
   void onMouseMoved(int x, int y)
   {
     renderer->mouse_current_x = x;
     renderer->mouse_current_y = y;
     last_frame_x = x;
     last_frame_y = y;
   }
   void onMouseDragged(int x, int y)
   {
     if (isImageSelected)
     {
       int delta_x = x - last_frame_x;
       int delta_y = y - last_frame_y;

       imageSelected->changeImagePosition(delta_x, delta_y);

     }
     last_frame_x = x;
     last_frame_y = y;

   }
   void onMousePressed(int x, int y)
   {
      for (auto &im: renderer->images)
      {
        std::cout << "image : " << im.image_origin_x << " " << im.image_origin_y << std::endl;
        std::cout << "width height : " << im.image_width << " " << im.image_heigth << std::endl;
        std::cout << "click : " << x << " " << y << std::endl;
        if (x > im.image_origin_x &&
            x < (im.image_width + im.image_origin_x) &&
            y > im.image_origin_y &&
            y < (im.image_heigth + im.image_origin_y))
            {
              imageSelected = &im;
              isImageSelected = true;
            }
      }
   }
   void onMouseReleased(int x, int y)
   {
     isImageSelected = false;
   }
   void drawCursor()
   {
      image.draw(ofGetMouseX() - 10, ofGetMouseY() - 10, 50, 45 );
   }

 private:
   int last_frame_x;
   int last_frame_y;
   bool isImageSelected = false;
   ofImage image;
   imageStruct* imageSelected;
   Renderer* renderer;
};
