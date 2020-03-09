

#include "square.h"

Square::Square(int _posX, int _posY, int _width, int _height, int _thickness,
               ofColor &_fill_Color, ofColor &_border_Color) :
        Primitive(_posX, _posY, _width, _height, _thickness, _fill_Color, _border_Color) {
    prim_size++;
    height = width;
    type = SceneObjectType::square;
}

Square::Square() : Primitive() {
    prim_size++;
    type = SceneObjectType::square;
}

void Square::draw() {

    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(0);
    ofDrawRectangle(position_x - (width / 2), position_y - (width / 2), width, width);

    ofNoFill();
    ofSetColor(borderColor);
    ofSetLineWidth(thickness * 10);
    ofDrawRectangle(position_x - (width / 2), position_y - (width / 2), width, width);
    ofSetColor(255, 255, 255);
}

void Square::translate(int x, int y) {
    position_x += x;
    position_y += y;
    //width += x;
    // height += y;
}


void Square::update() {
    height = width;
}


Square::~Square() {};
