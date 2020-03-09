#include "sphere.h"

Sphere::Sphere(float _posX, float _posY, float _width, float _height, ofColor &_fill_Color) {
    position_x = _posX;
    position_y = _posY;
    width = _width;
    height = _height;
    r = _width;

    sphere.setRadius(r);
    sphere.setPosition(-_width * .5 + _width * 2 / 4.f, _height * 1.1 / 6.f, 0);

    boundBox.setScale(r / 5);
    boundBox.setPosition(-_width * .5 + _width * 2 / 4.f, _height * 1.1 / 6.f, 0);
    type = SceneObjectType3D::sphere;
}

Sphere::Sphere() {
    r = 100;
    type = SceneObjectType3D::sphere;
}

void Sphere::draw() {
    ofFill();
    ofSetColor(fillColor);
    sphere.draw();
    ofNoFill();
    boundBox.draw();
}


void Sphere::setRadius(float _r) {
    r = _r;
}

float Sphere::getRadius() {
    return r;
}

void Sphere::update() {
    sphere.setRadius(r);
}

void Sphere::translate(float x, float y) {
    position_x += x;
    position_y += y;
}

Sphere::~Sphere() {};
