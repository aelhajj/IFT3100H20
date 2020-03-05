

#include "primitive.h"

Primitive::Primitive(int _posX, int _posY, int _width, int _height, int _thickness, ofColor &_fillColor,
                     ofColor &_borderColor) {
    position_x = _posX;
    position_y = _posY;
    thickness = _thickness;
    fillColor = _fillColor;
    borderColor = _borderColor;
    width = _width;
    height = _height;
}

ofColor Primitive::getFillColor() {
    return fillColor;
}

void Primitive::setFillColor(ofColor _fillColor) {
    fillColor = _fillColor;
}

ofColor Primitive::getBorderColor() {
    return borderColor;
}

void Primitive::setBorderColor(ofColor _borderColor) {
    borderColor = _borderColor;
}

int Primitive::getThickness() {
    return thickness;
}

void Primitive::setThickness(int _thickness) {
    thickness = _thickness;
}

Primitive::~Primitive() {}

int Primitive::prim_size = 0;