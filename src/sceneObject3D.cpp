
#include "sceneObject3D.h"

tuple<int, int> SceneObject3D::getPosition() {
    return make_tuple(position_x, position_y);
}

void SceneObject3D::setPosition(int _posX, int _posY) {
    position_x = _posX;
    position_y = _posY;
}

void SceneObject3D::info() {
    cout << "Pos x: " << position_x
         << " Pos y: " << position_y
         << " width: " << width
         << " height: " << height << endl;
}

int SceneObject3D::getHeight() {
    return height;
}

void SceneObject3D::setHeight(int _height) {
    height = _height;
}

int SceneObject3D::getWidth() {
    return width;
}

void SceneObject3D::setWidth(int _width) {
    width = _width;
}

void SceneObject3D::translate(int x, int y) {
    position_x += x;
    position_y += y;
}

void SceneObject3D::zoomIn() {
    float old_scale = scale;
    scale += 0.25;
}

void SceneObject3D::zoomOut() {
    if (scale > 0.25)
        scale -= 0.25;
}

void SceneObject3D::rotate() {
    rotation += 5;
}

