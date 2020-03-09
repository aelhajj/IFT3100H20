
#include "point.h"

Poin::Poin(int _posX, int _posY, int _width, int _height, int _thickness,
           ofColor &_fill_Color, ofColor &_border_Color) :
        Primitive(_posX, _posY, _width, _height, _thickness, _fill_Color, _border_Color) {
    prim_size++;
    r = 10;
    type = SceneObjectType::point;
}

Poin::Poin() : Primitive() {
    prim_size++;
    type = SceneObjectType::point;
}

void Poin::draw() {

    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(0);
    ofSetCircleResolution(100);
    ofDrawCircle(position_x, position_y, r);
    ofSetColor(255, 255, 255);

}

void Poin::translate(int x, int y) {
    position_x += x;
    position_y += y;
}

void Poin::update() {
    r = 10;
}


Poin::~Poin() {};
