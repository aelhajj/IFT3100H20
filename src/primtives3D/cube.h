#ifndef CUBE_H
#define CUBE_H

#include "primitive3D.h"
#include <cmath>

class Cube : public Primitive3D {
public:
    Cube(float _posX, float _posY, float _width, float _height, ofColor &fill_Color);

    Cube();

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

    ~Cube();

    ofBoxPrimitive cube;
    ofNode boundBox;

};

#endif
