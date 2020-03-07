
#include "cylinder.h"

Cylinder::Cylinder(float _posX, float _posY, float _width, float _height, ofColor &_fill_Color) {
    position_x = _posX;
    position_y = _posY;
    width = _width;
    height = _height;
    
    cylinder.set(width*.7, height*2.2);
    cylinder.setPosition( -_width * .5 + _width *  2/4.f, _height *  1.1/6.f, 0);

    boundBox.setScale(width/4);
    boundBox.setPosition(-_width * .5 + _width *  2/4.f, _height *  1.1/6.f, 0);
    type = SceneObjectType3D::cylinder;
}

Cylinder::Cylinder() {
    //r = 100;
    type = SceneObjectType3D::cylinder;
}

void Cylinder::draw() {
    ofFill();
    ofSetColor(fillColor);
    cylinder.draw();
    ofNoFill();
    boundBox.draw();
}

void Cylinder::update() {
    cylinder.set(width *5.75, height*5.75);
}

void Cylinder::translate(float x, float y) {
    position_x += x;
    position_y += y;
}

Cylinder::~Cylinder() {};
