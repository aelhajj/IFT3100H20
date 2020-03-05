#pragma once

#include "ofMain.h"
#include <vector>


class SceneObject {
public:

    void update();

    void addChild(SceneObject &child);

    
    tuple<int, int> getPosition();
    void setPosition(int _posX, int _posY);

    int getWidth();
    void setWidth(int _width);

    int getHeight();
    void setHeight(int _height);

    int getThickness();
    void setThickness(int _thickness);

    bool getSelected(int _posX, int _posY);
    void setSelected(bool _select);

    void setScale(float _scale);
    float getScale();

    virtual void draw() = 0;

    void translate(int _x, int _y);

    void rotate();

    void zoomIn();

    void zoomOut();

    void info();

    int position_x;
    int position_y; 
    int width;
    int height;
    float rotation = 0;
    float scale = 1;
    bool isSelected;

private:
    std::vector<SceneObject *> children;
};
