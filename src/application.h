

#pragma once

#include "ofMain.h"
#include "renderer.h"
#include "cursor.h"
#include "ofxDatGui.h"
#include "actions.h"

class Application : public ofBaseApp {
public:

    Actions *actions;
    Renderer renderer;
    // Mode 3D
    float time_current;
    float time_last;
    float time_elapsed;

    bool is_key_press_up;
    bool is_key_press_down;
    bool is_key_press_left;
    bool is_key_press_right;

    int nbClick = 0;

    ofxDatGuiButton *boutonModeSwitcher;

    ofxDatGuiButton *boutonImporter;
    ofxDatGuiButton *boutonRogner;
    ofxDatGuiButton *boutonHistogram;
    ofxDatGuiButton *boutonModel3D;
    ofxDatGuiButton *boutonRotate3D;
    ofxDatGuiButton *boutonBox3D;
    ofxDatGuiButton *boutonMesh3D;

    ofxDatGuiDropdown *menuCursor;
    ofxDatGuiDropdown *menu3DShape;
    ofxDatGui *gui;

    //ofParameter<ofColor> param_color_background;
    //ofParameter<ofColor> param_color_stroke;
    //ofParameter<ofColor> param_color_fill;

    //ofParameter<int> param_stroke_weight;

    ofxDatGuiColorPicker *background_color_picker;
    ofxDatGuiColorPicker *fill_color_picker;
    ofxDatGuiColorPicker *stroke_color_picker;
    ofxDatGuiSlider *stroke_slider;



    Cursor *cursor;

    void setup();

    void draw();

    //void drawGui();

    void update();

    void windowResized(int w, int h);

    void dragEvent(ofDragInfo dragInfo);

    void onButtonEvent(ofxDatGuiButtonEvent event);

    void onDropdownEvent(ofxDatGuiDropdownEvent event);

    void mouseMoved(int x, int y);

    void mouseDragged(int x, int y, int button);

    void mousePressed(int x, int y, int button);

    void mouseReleased(int x, int y, int button);

    void mouseEntered(int x, int y);

    void mouseExited(int x, int y);

    void keyReleased(int key);
    void keyPressed(int key);

    void openFileSelected(ofFileDialogResult openFileResult);

    void exit();
};
