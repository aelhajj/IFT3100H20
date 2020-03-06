
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

    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(0);
    ofDrawLine(position_x, position_y, width, height);

}


void Line::update() {

}


Line::~Line() {};
