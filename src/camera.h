#pragma once

#include "ofMain.h"
#include <vector>
#include "image.h"
#include "ofxAssimpModelLoader.h"

class Camera {
public:
    ofxAssimpModelLoader model;
    ofxAssimpModelLoader model2;
    ofLight light;
    ofNode boundBox;

    //Cameras
    ofCamera camera_front;
    ofCamera camera_back;
    ofCamera camera_left;
    ofCamera camera_right;

    ofCamera *camera;

    ofQuaternion camera_orientation;

    ofVec3f camera_position;
    ofVec3f camera_target;

    ofRectangle viewport1;
    ofRectangle viewport2;

    string camera_name;
    string camera_projection;

    float camera_near;
    float camera_far;

    float camera_fov;
    float camera_fov_delta;

    float offset_camera;
    float offset_color;
    float offset_scene;
    float offset_cube;

    float speed_translation;
    float time_current;
    float time_last;
    float time_elapsed;

    bool is_camera_move_forward;
    bool is_camera_move_backward;

    bool is_camera_perspective;
    bool is_split_screen;
    bool is_looking_model1 = true;

    void setup();

    void draw();

    void update();

    void reset();

    void changeObjectYoulookAt();

    void enableOrtho();

    void disableOrtho();

    void changePerspective();


};
