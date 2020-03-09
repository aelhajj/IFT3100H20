
#include "sceneObject.h"


void SceneObject::info() {
    cout << "Pos x: " << position_x
         << " Pos y: " << position_y
         << " width: " << width
         << " height: " << height << endl;
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

void SceneObject::undo(Actions action) {
    if (action == Actions::rotated) {
        rotation -= 5;
    }
    if (action == Actions::zoomedIn) {
        zoomOut();
    }
    if (action == Actions::zoomedOut) {
        zoomIn();
    }
    if (action == Actions::translated) {
        position_x = x_pos_before_translation;
        position_y = y_pos_before_translation;
    }
}
