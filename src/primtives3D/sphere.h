#ifndef SPHERE_H
#define SPHERE_H

#include "primitive3D.h"
#include <cmath>

class Sphere : public Primitive3D {
public:
    Sphere(float _posX, float _posY, float _width, float _height, ofColor &fill_Color);

    Sphere();

    void draw();

    ofColor getFillColor();

    void setFillColor(ofColor _fillColor);

    tuple<float, float> getPosition();

    void setPosition(float _posX, float _posY);

    float getWidth();

    void setWidth(float _width);

    float getHeight();

    void setHeight(float _height);

    float getRadius();

    void setRadius(float _r);

    void update();

    void translate(float x, float y);

    //Primitive *copy();

    ~Sphere();

    ofSpherePrimitive sphere;

    float r;

};

#endif
