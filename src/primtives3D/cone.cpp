#include "cone.h"

Cone::Cone(float _posX, float _posY, float _width, float _height, ofColor &_fill_Color) {
    position_x = _posX;
    position_y = _posY;
    width = _width;
    height = _height;
    
    cone.set(width*.75, height*2.2);
    cone.setPosition( -_width * .5 + _width *  2/4.f, _height *  1.1/6.f, 0);

    boundBox.setScale(width/5);
    boundBox.setPosition(-_width * .5 + _width *  2/4.f, _height *  1.1/6.f, 0);
    type = SceneObjectType3D::cone;
}

Cone::Cone() {
    //r = 100;
    type = SceneObjectType3D::cone;
}

void Cone::draw() {
    ofFill();
    ofSetColor(fillColor);
    cone.draw();
    ofNoFill();
    boundBox.draw();
}

void Cone::update() {
    cone.set(width *0.75, height*1.75);
}

void Cone::translate(float x, float y) {
    position_x += x;
    position_y += y;
}

Cone::~Cone() {};
