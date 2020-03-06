
#ifndef LINE_H
#define LINE_H

#include "primitive.h"
#include <cmath>

class Line : public Primitive {
public:
    Line(int _posX, int _posY, int _width, int _height, int _thickness,
           ofColor &fill_Color, ofColor &border_Color);

    Line();

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

    void setShape(int _posX, int _posY, int _setX, int _setY);

    void update();

    Primitive *copy();

    ~Line();

};

#endif