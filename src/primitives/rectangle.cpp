

#include "rectangle.h"

Rectangle::Rectangle(int _posX, int _posY, int _width, int _height, int _thickness,
               ofColor &_fill_Color, ofColor &_border_Color) :
        Primitive(_posX, _posY, _width, _height, _thickness, _fill_Color, _border_Color) {
    prim_size++;
    type = SceneObjectType::rectangle;
}

Rectangle::Rectangle() : Primitive() {
    prim_size++;
    type = SceneObjectType::rectangle;
}

void Rectangle::draw() {

    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(0);
    ofDrawRectangle(position_x - (width/2), position_y - (height/2), width, height);

    ofNoFill();
    ofSetColor(borderColor);
    ofSetLineWidth(thickness * 10);
    ofDrawRectangle(position_x - (width/2), position_y - (height/2), width, height);
    ofSetColor(255, 255, 255);
}

void Rectangle::translate(int x, int y) {
    position_x += x;
    position_y += y;
    //width += x;
   // height += y;
}


void Rectangle::update() {
}


Rectangle::~Rectangle() {};
