

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

    float time_current;
    float time_last;
    float time_elapsed;

    bool is_key_press_up;
    bool is_key_press_down;
    bool is_key_press_left;
    bool is_key_press_right;

    bool tone_mapping_type;

    int nbClick = 0;
    //int nbClick_2 = 0;

    ofxDatGuiButton *boutonModeSwitcher;

    ofxDatGuiButton *boutonFilterSwitch;

    //   ofxDatGuiButton *boutonMappingSwitch;
    //   ofxDatGuiButton *boutonTextureProceduraleSwitch;

    ofxDatGuiButton *boutonImporter;
    ofxDatGuiButton *boutonRogner;
    ofxDatGuiButton *boutonHistogram;
    ofxDatGuiButton *boutonModel3D;
    ofxDatGuiButton *boutonRotate3D;
    ofxDatGuiButton *boutonBox3D;
    ofxDatGuiButton *boutonMesh3D;
    ofxDatGuiButton *boutonAnim3D;
    ofxDatGuiButton *boutonMateriel;

    ofxDatGuiDropdown *menuCursor;
    ofxDatGuiDropdown *menu3DShape;
    ofxDatGui *gui;

    ofxDatGuiColorPicker *background_color_picker;
    ofxDatGuiColorPicker *fill_color_picker;
    ofxDatGuiColorPicker *stroke_color_picker;

    ofxDatGuiColorPicker *filter_tint_color_picker;

    ofxDatGuiColorPicker *ambiant_color_picker;
    ofxDatGuiColorPicker *diffuse_color_picker;
    ofxDatGuiColorPicker *specular_color_picker;

    ofxDatGuiSlider *filter_mix_slider;
    ofxDatGuiSlider *gamma_slider;
    ofxDatGuiSlider *exposure_slider;

    ofxDatGuiSlider *stroke_slider;
    ofxDatGuiSlider *metallic_slider;
    ofxDatGuiSlider *roughness_slider;
    ofxDatGuiSlider *occlusion_slider;
    ofxDatGuiSlider *brightness_slider;
    ofxDatGuiSlider *tesselation_in_slider;
    ofxDatGuiSlider *tesselation_out_slider;

    ofxDatGuiToggle *toggle_test;
    ofxDatGuiToggle *toggle_mapping_tonal;
    ofxDatGuiToggle *toggle_textural_procedure;

    ofxDatGuiToggle *toggle_PBR_shader;
    ofxDatGuiToggle *toggle_illuminate_shader;

    ofxDatGuiToggle *toggle_light_ambiant;
    ofxDatGuiToggle *toggle_light_direct;
    ofxDatGuiToggle *toggle_light_point;
    ofxDatGuiToggle *toggle_light_spot;

    Cursor *cursor;

    void setup();

    void draw();


    void update();

    void windowResized(int w, int h);

    void dragEvent(ofDragInfo dragInfo);

    void onButtonEvent(ofxDatGuiButtonEvent event);

    void onDropdownEvent(ofxDatGuiDropdownEvent event);

    void onToggleEvent(ofxDatGuiToggleEvent event);

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
