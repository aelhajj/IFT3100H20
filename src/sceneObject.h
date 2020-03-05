#pragma once

#include "ofMain.h"
#include <vector>


class SceneObject {
public:
    void update() {
        for (SceneObject *child:children) {
            child->update();
        }
    }

    void addChild(SceneObject &child) {
        children.push_back(&child);
    }

    virtual void draw() = 0;

    virtual void translate(int x, int y) = 0;

    virtual void rotate() = 0;

    virtual void zoomIn() = 0;

    virtual void zoomOut() = 0;

private:
    std::vector<SceneObject *> children;
};
