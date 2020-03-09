
#ifndef POIN_H
#define POIN_H

#include "primitive.h"
#include <cmath>

class Poin : public Primitive {
public:
    Poin(int _posX, int _posY, int _width, int _height, int _thickness,
         ofColor &fill_Color, ofColor &border_Color);

    Poin();

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

    void update();

    void translate(int x, int y);

    Primitive *copy();

    ~Poin();

    int r = 1;
};

#endif