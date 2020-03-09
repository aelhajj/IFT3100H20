
#include "line.h"

Line::Line(int _posX, int _posY, int _width, int _height, int _thickness,
           ofColor &_fill_Color, ofColor &_border_Color) :
        Primitive(_posX, _posY, _width, _height, _thickness, _fill_Color, _border_Color) {
    prim_size++;
    type = SceneObjectType::line;
}

Line::Line() : Primitive() {
    prim_size++;
    type = SceneObjectType::line;
}

void Line::draw() {
    info();
    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(0);
    int x2 = position_x + (width / 2);
    int y2 = position_y + (height / 2);
    ofDrawLine(position_x - (width / 2), position_y - (height / 2), x2, y2);
    ofSetColor(255, 255, 255);
}


void Line::update() {

}

void Line::translate(int x, int y) {
    position_x = x;
    position_y = y;
    height += y;
    width += x;
}


Line::~Line() {};
