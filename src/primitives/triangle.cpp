

#include "triangle.h"

Triangle::Triangle(int _posX, int _posY, int _posX2, int _posY2, int _thickness,
               ofColor &_fill_Color, ofColor &_border_Color) :
        Primitive(_posX, _posY, _posX2, _posY2, _thickness, _fill_Color, _border_Color) {
    x3 = (position_x + width) / 2;
    y3 = (position_y + height) / 2;
    prim_size++;
    type = SceneObjectType::triangle;
}

Triangle::Triangle() : Primitive() {
    prim_size++;
    type = SceneObjectType::triangle;
}

void Triangle::draw() {
    int x1 = position_x - (width/2);
    int y1 = position_y - (height/2);
    int x2 = position_x + (width/2);
    int y2 = position_y - (height/2);
    int x3 = position_x;
    int y3 = position_y + (height/2);

    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(0);
    ofDrawTriangle(x1, y1, x2, y2, x3, y3);

    ofNoFill();
    ofSetColor(borderColor);
    ofSetLineWidth(thickness * 10);
    ofDrawTriangle(x1, y1, x2, y2, x3, y3);
    ofSetColor(255, 255, 255);
}


void Triangle::update() {
    x3 = (position_x + width) / 2;
    y3 = (position_y + height) / 2;
}


void Triangle::changeShape(int x, int y) {
    position_x += x;
    position_y += y;
    width += x;
    height += y;
    x3 += x;
    y3 += y;
}

void Triangle::translate(int x, int y) {
    position_x += x;
    position_y += y;
}


Triangle::~Triangle() {};
