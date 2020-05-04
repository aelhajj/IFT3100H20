

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
#include "primtives3D/cube.h"
#include "primtives3D/cone.h"
#include "primtives3D/cylinder.h"
#include "camera.h"
#include "model3D.h"
#include "raytracer.h"
#include "parametric.h"
#include "catmull_rom.h"
#include "ofxShaderSelect.h"

enum class ShaderType {
    color_fill, lambert, gouraud, phong, blinn_phong
};


class Renderer {
public:
    int f;
    std::vector<ImageStruct *> images;
    ofImage image;
    ofImage image_source;
    ofImage image_destination; // pour les modifications sur la texture courante
    ofImage texture;

    Camera *camera = new Camera();
    Raytracer *raytracer = new Raytracer();
    Catmull_Rom *catmull_rom = new Catmull_Rom();
    enum modes {
        is2D, is3D, isCamera, isRaytracer, isParametric, isCatmull, isModernIllumination
    };

    Parametric *parametric_renderer = new Parametric();

    ConvolutionKernel kernel_type;

    modes Mode = modes::is2D; // si mode est en 2D : true, si 3D : false
    bool isMode2D = false;
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

    int position_3d_x;
    int position_3d_y;

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

    ofNode node;

    ofShader shader;

    ofShader shader_lights;

    ofShader shader_texture_procedurale;

    ofxShaderSelect shader_tesselation;

    ofShader shader_tesselation_pass;

    ofVbo vbo;

    // shader d'illumination
    ShaderType shader_active;

    ofShader *shader_illuminate;

    ofShader shader_color_fill;
    ofShader shader_lambert;
    ofShader shader_gouraud;
    ofShader shader_phong;
    ofShader shader_blinn_phong;

    ofLight light;

    ofLight light_point;
    ofLight light_spotlight;
    ofLight light_directional;
    ofLight light_spot;


    ofColor light_ambient;

    ofMaterial material_cube;
    ofMaterial material_sphere;
    ofMaterial material_teapot;


    ofxAssimpModelLoader teapot;
    ofSpherePrimitive sphere;

    ofVec3f position_cube;
    ofVec3f position_sphere;
    ofVec3f position_teapot;

    ofVec3f light_vector;
    ofVec3f diffuse_vector;
    ofVec3f ambiant_vector;
    ofVec3f specular_vector;
    ofVec3f translation_vector;
    ofVec4f rotation_vector;

    int inner_level;
    int outer_level;

    ofQuaternion orientation_directional;
    ofQuaternion orientation_spot;


    string shader_name;

    float oscillation;

    float scale_cube;
    float scale_sphere;
    float scale_teapot;

    float oscillation_frequency;
    float oscillation_amplitude;

    float speed_motion;

    bool illuminate_toggle;
    bool lights_toggle;
    bool tesselation_toggle;
    bool texture_toggle;

    bool is_active_ligh_ambient = true;
    bool is_active_light_directional = true;
    bool is_active_light_point = true;
    bool is_active_light_spot = true;

    ofColor material_color_ambient;
    ofColor material_color_diffuse;
    ofColor material_color_specular;

    float material_metallic;
    float material_roughness;
    float material_occlusion;
    float material_brightness;

    glm::vec3 material_fresnel_ior;

    ofImage texture_diffuse;
    ofImage texture_metallic;
    ofImage texture_roughness;
    ofImage texture_occlusion;

    ofColor light_color;
    float light_intensity;
    bool light_motion;
    bool material_toggle;

    ofColor filter_tint;
    float filter_mix;

    float center_x;
    float center_y;

    float offset_x;
    float offset_z;

    float initial_x;
    float initial_z;

    float delta_x;
    float delta_z;

    float camera_offset;

    float speed;

    float tone_mapping_exposure;
    float tone_mapping_gamma;

    bool tone_mapping_toggle;
    bool tone_mapping_aces;

    bool texture_procedurale_toggle;

    string kernel_name;

    int image_width;
    int image_height;


    bool is_flip_axis_y;

    //For raycast
    int count = 0;

    void setup();

    void draw();

    void reset();

    void update();

    void draw_zone(float x1, float y1, float x2, float y2) const;

    void draw_cursor(float x, float y) const;

    void draw_histogram();

    void add_primitive(SceneObjectType type);

    void add_primitive3D(SceneObjectType3D type);

    void add_Model3D();

    void image_export() const;

    void showBox3D();

    void rotate3D();

    void showMesh3D();

    void showAnim3D();

    void filter();

    void illuminate();

    float oscillate(float time, float frequency, float amplitude);

    void draw_tesselation();

    void lighting_on();

    void lighting_off();

    ~Renderer();

    ofEasyCam cam;


};
