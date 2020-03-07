#ifndef COMPOSEDSHAPE_H
#define COMPOSEDSHAPE_H

#include "sceneObject.h"
#include "composedShape.h"
#include "primitives/square.h"

class ComposedShape : public SceneObject
{

public:
    void draw();
    virtual void translate(int x, int y);
    std::vector<Primitive *> primitives;
};




#endif