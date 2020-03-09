#include "cube.h"

Cube::Cube(float _posX, float _posY, float _width, float _height, ofColor &_fill_Color) {
    position_x = _posX;
    position_y = _posY;
    width = _width;
    height = _height;

    cube.set(width * 1.75);
    cube.setPosition(-_width * .5 + _width * 2 / 4.f, _height * 1.1 / 6.f, 0);

    boundBox.setScale(width / 3);
    boundBox.setPosition(-_width * .5 + _width * 2 / 4.f, _height * 1.1 / 6.f, 0);
    type = SceneObjectType3D::cube;


    for (int i = 0; i < ofBoxPrimitive::SIDES_TOTAL; i++) {
        cube_sides[i] = cube.getSideMesh(i);
    }
}

Cube::Cube() {
    type = SceneObjectType3D::cube;

}

void Cube::draw() {
    ofNoFill();
    ofSetColor(fillColor);
    if (is_mesh_mode) {
        cube.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        cube.transformGL();
        rotate();
        getMeshes();
        cube.restoreTransformGL();
    } else {
        ofPushMatrix();
        ofNoFill();
        rotate();
        cube.setMode(OF_PRIMITIVE_TRIANGLES);
        cube.draw();
        ofPopMatrix();
    }

    if (show_box) {
        ofNoFill();
        boundBox.draw();
    }
}

void Cube::update() {
    cube.set(width * 1.75);
}

void Cube::translate(float x, float y, float z) {
    position_x += x;
    position_y += y;
    position_z += z;
    cube.setPosition((-width * .5 + width * 2 / 4.f) + position_x, (height * 1.1 / 6.f) + position_y, 0 + position_z);

}

void Cube::getMeshes() {
    for (int i = 0; i < ofBoxPrimitive::SIDES_TOTAL; i++) {
        ofPushMatrix();
        if (!is_animate)
            ofTranslate(cube_sides[i].getNormal(0) * sin(ofGetElapsedTimef()) * 50);
        cube_sides[i].drawWireframe();
        ofPopMatrix();
    }
}

void Cube::rotate() {
    if (is_rotating) {
        ofRotateDeg(sin(ofGetElapsedTimef() * 5) * RAD_TO_DEG, 10, 1, 1);
        ofRotateDeg(cos(ofGetElapsedTimef() * 5) * RAD_TO_DEG, 1, 10, 10);
    }
}


Cube::~Cube() {};
