

#pragma once

#include "ofMain.h"
#include <vector>
#include "image.h"
#include "primitives/circle.h"
#include "primitives/line.h"
#include "primitives/point.h"
#include "primitives/rectangle.h"
#include "primitives/triangle.h"
#include "star.h"
#include "primtives3D/sphere.h"


// structure d'un localisateur de transformation
struct Locator
{
  float position[3];   // 3 * 4 = 12 octets
  float rotation[3];   // 3 * 4 = 12 octets
  float proportion[3]; // 3 * 4 = 12 octets
};                     //       = 36 octets


class Renderer {
public:
    int f;
    std::vector<ImageStruct *> images;
    ofImage image;

    //std::vector <Primitive*> shapes;

    bool isMode2D; // si mode est en 2D : true, si 3D : false
    
    int index = 0;
    std::vector<SceneObject *> objects;
    std::vector<Primitive *> shapes;

    std::vector<SceneObject3D *> objects3D;
    SceneObject *sceneObjectSelected = nullptr;
    ImageStruct *imageSelected = nullptr;
    Primitive *shapeSelected = nullptr;

    SceneObjectType draw_mode;

    int screen_height = 900;
    int screen_width = 900;

    int offset_vertical;
    int offset_horizontal;

    int mouse_press_x;
    int mouse_press_y;

    int mouse_current_x;
    int mouse_current_y;

    bool is_mouse_button_pressed;
    bool is_ready_croping = false;
    bool is_draw_mode = false;

    ofColor background_color;
    ofColor stroke_color;
    ofColor fill_color;
    int stroke_size;

    int radius;

    bool viewHist;

    std::vector<int> croping_zone;

    std::vector<int> draw_space;

    // Mode 3D : 

   // Locator* locators;

    ofNode node;

   // ofVec3f vector_position;
   // ofVec3f vector_rotation;
   // ofVec3f vector_proportion;

    float center_x;
    float center_y;

    float offset_x;
    float offset_z;

    float delta_x;
    float delta_z;

    float speed;

   // int locator_count;

  //  int locator_buffer_head;

    bool is_flip_axis_y;

  //  bool is_active_translation;
   // bool is_active_rotation;
   // bool is_active_proportion;

    void setup();

    void draw();

    void reset();

    void update();

    void draw_zone(float x1, float y1, float x2, float y2) const;

    void draw_cursor(float x, float y) const;

    void draw_histogram();

    void add_primitive(SceneObjectType type);

 //   void dispatch_locators(int count, float range);

    void draw_locator(float scale);

    ~Renderer();

    ofEasyCam cam;

};
