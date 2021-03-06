
#include "sceneObject3D.h"


void SceneObject3D::info() {
    cout << "Pos x: " << position_x
         << " Pos y: " << position_y
         << " width: " << width
         << " height: " << height << endl;
}


void SceneObject3D::translate(float x, float y, float z) {
    position_x += x;
    position_y += y;
    position_z += z;
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

