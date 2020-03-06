
#include "sceneObject.h"

tuple<int, int> SceneObject::getPosition() {
    return make_tuple(position_x, position_y);
}

void SceneObject::setPosition(int _posX, int _posY) {
    position_x = _posX;
    position_y = _posY;
}

void SceneObject::info() {
    cout << "Pos x: " << position_x
         << " Pos y: " << position_y
         << " width: " << width
         << " height: " << height << endl;
}

int SceneObject::getHeight() {
    return height;
}

void SceneObject::setHeight(int _height) {
    height = _height;
}

int SceneObject::getWidth() {
    return width;
}

void SceneObject::setWidth(int _width) {
    width = _width;
}

void SceneObject::translate(int x, int y) {
    position_x += x;
    position_y += y;
}

void SceneObject::zoomIn() {
    float old_scale = scale;
    scale += 0.25;
}

void SceneObject::zoomOut() {
    if (scale > 0.25)
        scale -= 0.25;
}

void SceneObject::rotate() {
    rotation += 5;
}

