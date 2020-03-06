// IFT3100H20_ImageImport/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include <vector>
#include "image.h"
#include "primitives/circle.h"


class Renderer {
public:
    int f;
    std::vector<ImageStruct *> images;
    ofImage image;

    //std::vector <Primitive*> shapes;
    int index = 0;
    std::vector<SceneObject *> objects;
    std::vector<Primitive *> shapes;
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

    void setup();

    void draw();

    void reset();

    void update();

    void draw_zone(float x1, float y1, float x2, float y2) const;

    void draw_cursor(float x, float y) const;

    void draw_histogram();

    void add_primitive(SceneObjectType type);

    ofEasyCam cam;

};
