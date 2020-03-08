#pragma once

#include "ofMain.h"
#include <vector>

enum class SceneObjectType {
    none, point, line, rectangle, triangle, circle, image, square, quatrefoil
};

class SceneObject {
public:
    enum Actions {croped, translated, rotated, zoomedIn, zoomedOut};


 /*   void addChild(SceneObject &child);

    tuple<int, int> getPosition();

    void setPosition(int _posX, int _posY);

    //void SceneObject::setType(SceneObjectType _type);

    int getWidth();

    void setWidth(int _width);

    int getHeight();

    void setHeight(int _height);

    int getThickness();

    void setThickness(int _thickness);

    void setScale(float _scale);

    float getScale();*/

    virtual void draw() = 0;

    virtual void translate(int _x, int _y);

    void rotate();

    void zoomIn();

    void zoomOut();

    void info();

    void undo(Actions action);

    virtual void update() = 0;

    int position_x;
    int position_y;
    int x_pos_before_translation;
    int y_pos_before_translation;
    int width;
    int height;
    float rotation = 0;
    float scale = 1;
    bool isSelected;
    SceneObjectType type = SceneObjectType::none;
    int thickness;

    ofColor fillColor;
    ofColor borderColor;

//private:
    //std::vector<SceneObject *> children;

};
