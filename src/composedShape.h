#ifndef COMPOSEDSHAPE_H
#define COMPOSEDSHAPE_H

#include "sceneObject.h"
#include "composedShape.h"
#include "primitives/square.h"

// Classe pour les objets composées en 2D, section 3.4 
class ComposedShape : public SceneObject {

public:
    void draw();

    virtual void translate(int x, int y);

    std::vector<Primitive *> primitives;
};


#endif