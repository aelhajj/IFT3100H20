// IFT3100H19_CurveHermite/renderer.cpp
// Classe responsable du rendu de l'application.

#include "catmull_rom.h"

void Catmull_Rom::setup() {
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);
    ofSetSphereResolution(32);
    ofDisableDepthTest();

    // paramètres
    line_resolution = 100;
    line_width_outline = 4.0f;
    line_width_curve = 8.0f;

    radius = 32.0f;
    scale = 10.0f;
    offset = 64.0f;

    motion_speed = 250.0f;

    // initialisation des sommets de la ligne
    for (index = 0; index <= line_resolution * 2; ++index)
        line_renderer.addVertex(ofPoint());

    // courbe au lancement de l'application

    // initialisation de la scène
    reset();
}

void Catmull_Rom::reset() {
    // initialisation des variables
    framebuffer_width = ofGetWidth();
    framebuffer_height = ofGetHeight();

    // ratios de positionnement dans la fenêtre
    float w_1_8 = framebuffer_width / 3.5f;
    float w_1_4 = framebuffer_width / 2.5f;
    float w_1_2 = framebuffer_width / 1.5f;
    float w_3_4 = framebuffer_width * 3.0f / 4.0f;
    float w_7_8 = framebuffer_width * 7.0f / 8.0f;
    float h_1_5 = framebuffer_height / 5.0f;
    float h_1_3 = framebuffer_height / 3.0f;
    float h_4_5 = framebuffer_height * 3.0f / 5.0f;

    initial_position1 = {w_1_8, h_4_5, 0};
    initial_position2 = {w_1_4, h_1_3, 0};
    initial_position3 = {w_1_2, h_1_5, 0};
    initial_position4 = {w_3_4, h_1_3, 0};
    initial_position5 = {w_7_8, h_4_5, 0};
    initial_position6 = {w_7_8, h_1_3, 0};
    initial_position7 = {w_3_4, h_4_5, 0};

    // paramètres selon le type de courbe


    curve_name = "Catmull Rom";

    ctrl_point1 = initial_position1;
    ctrl_point2 = initial_position2;
    ctrl_point3 = initial_position3;
    ctrl_point4 = initial_position5;
    ctrl_point5 = initial_position4;
    ctrl_point6 = initial_position6;
    ctrl_point7 = initial_position7;

    selected_ctrl_point = &ctrl_point2;


    delta_x = motion_speed;
    delta_y = motion_speed;

    ofLog() << "<reset>";
}

void Catmull_Rom::update() {
    updateFloatAnimation();
    for (index = 0; index <= line_resolution; ++index) {
        // paramètres selon le type de courbe

        catmull_rom(
                index / (float) line_resolution,
                ctrl_point1.x, ctrl_point1.y, ctrl_point1.z,
                ctrl_point2.x, ctrl_point2.y, ctrl_point2.z,
                ctrl_point3.x, ctrl_point3.y, ctrl_point3.z,
                ctrl_point4.x, ctrl_point4.y, ctrl_point4.z,
                position.x, position.y, position.z);


        line_renderer[index] = position;
    }
    for (index = line_resolution; index <= line_resolution * 2; ++index) {
        catmull_rom(
                (index - line_resolution) / (float) line_resolution,
                ctrl_point2.x, ctrl_point2.y, ctrl_point2.z,
                ctrl_point3.x, ctrl_point3.y, ctrl_point3.z,
                ctrl_point4.x, ctrl_point4.y, ctrl_point4.z,
                ctrl_point5.x, ctrl_point5.y, ctrl_point5.z,
                position.x, position.y, position.z);

        line_renderer[index] = position;
    }

}

void Catmull_Rom::updateFloatAnimation() {
    if (counter % 50 < 25) {
        animation_float += 0.5;
        counter++;
        ctrl_point1.y += animation_float;
        ctrl_point2.y -= animation_float;
        ctrl_point3.y += animation_float;
        ctrl_point4.y -= animation_float;
    } else {
        animation_float -= 0.5;
        counter++;
        ctrl_point1.y -= animation_float;
        ctrl_point2.y += animation_float;
        ctrl_point3.y -= animation_float;
        ctrl_point4.y += animation_float;
    }
    if (counter == 10000) {
        counter = 1;
    }


}


void Catmull_Rom::draw() {
    update();

    // dessiner les positions initiales
    ofSetColor(63, 63, 63);
    ofDrawEllipse(initial_position1.x, initial_position1.y, radius / 2.0f, radius / 2.0f);
    ofDrawEllipse(initial_position2.x, initial_position2.y, radius / 2.0f, radius / 2.0f);
    ofDrawEllipse(initial_position3.x, initial_position3.y, radius / 2.0f, radius / 2.0f);
    ofDrawEllipse(initial_position4.x, initial_position4.y, radius / 2.0f, radius / 2.0f);
    ofDrawEllipse(initial_position5.x, initial_position5.y, radius / 2.0f, radius / 2.0f);

    // dessiner la ligne contour
    ofSetColor(0, 0, 255);
    ofSetLineWidth(line_width_outline);
    ofDrawLine(ctrl_point1.x, ctrl_point1.y, ctrl_point2.x, ctrl_point2.y);
    ofDrawLine(ctrl_point4.x, ctrl_point4.y, ctrl_point5.x, ctrl_point5.y);


    // dessiner la courbe
    ofSetColor(0, 255, 0);
    ofSetLineWidth(line_width_curve);
    line_renderer.draw();

    // dessiner les points de contrôle
    ofSetColor(255, 0, 0);
    ofDrawEllipse(ctrl_point1.x, ctrl_point1.y, radius, radius);
    ofDrawEllipse(ctrl_point2.x, ctrl_point2.y, radius, radius);
    ofDrawEllipse(ctrl_point3.x, ctrl_point3.y, radius, radius);
    ofDrawEllipse(ctrl_point4.x, ctrl_point4.y, radius, radius);
    ofDrawEllipse(ctrl_point5.x, ctrl_point5.y, radius, radius);
}
