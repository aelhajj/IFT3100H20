

#include "triangle.h"

Triangle::Triangle(int _posX, int _posY, int _posX2, int _posY2, int _thickness,
               ofColor &_fill_Color, ofColor &_border_Color) :
        Primitive(_posX, _posY, _posX2, _posY2, _thickness, _fill_Color, _border_Color) {
    x3 = width / 2;
    y3 = height / 2;
    prim_size++;
    type = SceneObjectType::triangle;
}

Triangle::Triangle() : Primitive() {
    prim_size++;
    type = SceneObjectType::triangle;
}

void Triangle::draw() {
    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(0);
    ofDrawTriangle(position_x, position_y, width, height, x3, y3);

    ofNoFill();
    ofSetColor(borderColor);
    ofSetLineWidth(thickness * 10);
    ofDrawTriangle(position_x, position_y, width, height, x3, y3);
    ofSetColor(255, 255, 255);
}


void Triangle::update() {
    x3 = width / 2;
    y3 = height / 2;
}


Triangle::~Triangle() {};
