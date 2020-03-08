
#ifndef PRIMITIVE3D_H
#define PRIMITIVE3D_H

#include "ofMain.h"
#include <tuple>
#include "sceneObject3D.h"

class Primitive3D : public SceneObject3D {
public:
    Primitive3D(int _posX, int _posY, int _width, int _height, ofColor &_fillColor) ;

    Primitive3D();

    virtual void draw() {}

    virtual void translate(int x, int y) {}

    ~Primitive3D();



};

#endif
