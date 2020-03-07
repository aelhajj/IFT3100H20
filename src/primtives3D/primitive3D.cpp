

#include "primitive3D.h"

Primitive3D::Primitive3D(int _posX, int _posY, int _width, int _height, ofColor &_fillColor) {
    position_x = _posX;
    position_y = _posY;
    fillColor = _fillColor;
    width = _width;
    height = _height;
}

Primitive3D::Primitive3D() {

}


Primitive3D::~Primitive3D() {}
