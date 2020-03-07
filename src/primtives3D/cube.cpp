#include "cube.h"

Cube::Cube(float _posX, float _posY, float _width, float _height, ofColor &_fill_Color) {
    position_x = _posX;
    position_y = _posY;
    width = _width;
    height = _height;
    
    cube.set(width *1.75);
    cube.setPosition( -_width * .5 + _width *  2/4.f, _height *  1.1/6.f, 0);

    boundBox.setScale(width/3);
    boundBox.setPosition(-_width * .5 + _width *  2/4.f, _height *  1.1/6.f, 0);
    type = SceneObjectType3D::cube;
}

Cube::Cube() {
    //r = 100;
    type = SceneObjectType3D::cube;
}

void Cube::draw() {
    ofFill();
    ofSetColor(fillColor);
    cube.draw();
    ofNoFill();
    boundBox.draw();
}

void Cube::update() {
    cube.set(width *1.75);
}

void Cube::translate(float x, float y) {
    position_x += x;
    position_y += y;
}

Cube::~Cube() {};
