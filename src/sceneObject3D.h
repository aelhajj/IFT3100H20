#pragma once

#include "ofMain.h"
#include <vector>

enum class SceneObjectType3D {
    none, sphere, cube, cone, cylinder
};

class SceneObject3D {
public:

    virtual void draw() = 0;

    virtual void translate(float _x, float _y, float _z);

    virtual void rotate();

    virtual void setTexture(ofImage imageTexture) {};

    void zoomIn();

    void zoomOut();

    void info();

    virtual void update() = 0;

    float position_x;
    float position_y;
    float position_z;
    int width;
    int height;
    float rotation = 0;
    float scale = 1;
    bool isSelected;
    SceneObjectType3D type = SceneObjectType3D::none;
    int thickness;

    ofColor fillColor;

    bool is_mesh_mode = false;
    bool show_box = false;
    bool is_rotating = false;
    bool is_animate = false;

    ofImage texture;
    bool textureMode = false;

};
