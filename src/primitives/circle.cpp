

#include "circle.h"

Circle::Circle(int _posX, int _posY, int _width, int _height, int _thickness,
               ofColor &_fill_Color, ofColor &_border_Color) :
        Primitive(_posX, _posY, _width, _height, _thickness, _fill_Color, _border_Color) {
    r = width / 2;
    prim_size++;
    type = SceneObjectType::circle;
}

Circle::Circle() : Primitive() {
    prim_size++;
    type = SceneObjectType::circle;
}

void Circle::draw() {

    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(0);
    ofSetCircleResolution(100);
    ofDrawCircle(position_x, position_y, r);

    ofNoFill();
    ofSetColor(borderColor);
    ofSetLineWidth(thickness * 10);
    ofSetCircleResolution(100);
    ofDrawCircle(position_x, position_y, r);
    ofSetColor(255, 255, 255);
}


void Circle::setRadius(int _r) {
    r = _r;
}

int Circle::getRadius() {
    return r;
}

void Circle::update() {
    r = width / 2;
}


Circle::~Circle() {};
