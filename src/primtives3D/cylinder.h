#ifndef CYLINDER_H
#define CYLINDER_H

#include "primitive3D.h"
#include <cmath>

class Cylinder : public Primitive3D {
public:
    Cylinder(float _posX, float _posY, float _width, float _height, ofColor &fill_Color);

    Cylinder();

    void draw();

    ofColor getFillColor();

    void setFillColor(ofColor _fillColor);

    tuple<float, float> getPosition();

    void setPosition(float _posX, float _posY);

    float getWidth();

    void setWidth(float _width);

    float getHeight();

    void setHeight(float _height);

    void update();

    void translate(float x, float y);

    ~Cylinder();

    ofCylinderPrimitive cylinder;
    ofNode boundBox;

};

#endif
