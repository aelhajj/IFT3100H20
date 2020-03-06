
#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "ofMain.h"
#include <tuple>
#include "sceneObject.h"

class Primitive : public SceneObject {
public:
    Primitive(int _posX, int _posY, int _width, int _height, int _thickness, ofColor &fill_Color,
              ofColor &border_Color);

    static int prim_size;

    virtual void draw() {}

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

    void setThickness(int _thickness);

    bool isSelected(int _posX, int _posY);

    void setShape(int _posX, int _posY, int _setX, int _setY);


    Primitive *copy();

    ~Primitive();

};

#endif