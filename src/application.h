

#pragma once

#include "ofMain.h"
#include "renderer.h"
#include "cursor.h"
#include "ofxDatGui.h"

class Application : public ofBaseApp {
public:

    Renderer renderer;
    ofxDatGuiButton *boutonImporter;
    ofxDatGuiButton *boutonRogner;
    ofxDatGuiButton *boutonHistogram;
    ofxDatGuiDropdown *menuCursor;

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

    void openFileSelected(ofFileDialogResult openFileResult);

    void exit();
};
