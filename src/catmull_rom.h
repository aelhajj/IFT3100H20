// IFT3100H19_CurveHermite/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

// énumération de types de courbe

// fonction d'évaluation d'une courbe de hermite (4 points de contrôle)

inline void catmull_rom(
        float t,
        float p1x, float p1y, float p1z,
        float p2x, float p2y, float p2z,
        float p3x, float p3y, float p3z,
        float p4x, float p4y, float p4z,
        float &x, float &y, float &z) {

    float tt = t * t;
    float ttt = tt * t;


    x = 0.5 *
        ((-t + 2 * tt - ttt) * p1x + (2 - 5 * tt + 3 * ttt) * p2x + (t + 4 * tt - 3 * ttt) * p3x + (-tt + ttt) * p4x);
    y = 0.5 *
        ((-t + 2 * tt - ttt) * p1y + (2 - 5 * tt + 3 * ttt) * p2y + (t + 4 * tt - 3 * ttt) * p3y + (-tt + ttt) * p4y);
    z = 0.5 *
        ((-t + 2 * tt - ttt) * p1z + (2 - 5 * tt + 3 * ttt) * p2z + (t + 4 * tt - 3 * ttt) * p3z + (-tt + ttt) * p4z);
}

class Catmull_Rom {
public:

    int counter = 1;
    float animation_float = 1;
    string curve_name;

    ofPolyline line_renderer;

    ofVec3f *selected_ctrl_point;

    ofVec3f ctrl_point1;
    ofVec3f ctrl_point2;
    ofVec3f ctrl_point3;
    ofVec3f ctrl_point4;
    ofVec3f ctrl_point5;
    ofVec3f ctrl_point6;
    ofVec3f ctrl_point7;

    ofVec3f initial_position1;
    ofVec3f initial_position2;
    ofVec3f initial_position3;
    ofVec3f initial_position4;
    ofVec3f initial_position5;
    ofVec3f initial_position6;
    ofVec3f initial_position7;

    ofVec3f position;

    ofVec3f tangent1;
    ofVec3f tangent2;

    float line_width_outline;
    float line_width_curve;

    float radius;
    float scale;
    float offset;

    float delta_x;
    float delta_y;

    float motion_speed;

    int framebuffer_width;
    int framebuffer_height;

    int line_resolution;

    int index;

    void setup();

    void update();

    void draw();

    void reset();

    void updateFloatAnimation();
};
