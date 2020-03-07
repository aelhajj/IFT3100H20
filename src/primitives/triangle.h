#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "primitive.h"
#include <cmath>

class Triangle : public Primitive {
public:
    Triangle(int _posX, int _posY, int _posX2, int _posY2, int _thickness,
           ofColor &fill_Color, ofColor &border_Color);

    Triangle();

    void draw();

    ofColor getFillColor();

    void setFillColor(ofColor _fillColor);

    ofColor getBorderColor();

    void setBorderColor(ofColor _borderColor);

    tuple<int, int> getPosition();

    void setPosition(int _posX, int _posY);

    int getWidth();

    void setWidth(int _width);

    int getHeight();

    void setHeight(int _height);

    int getThickness();

    void setThickness(float _thickness);

    void changeShape();

    void update();

    void translate(int x, int y);

    Primitive *copy();

    ~Triangle();

    int x1;
    int y1;

    int x2;
    int y2;

    int x3;
    int y3;

};

#endif