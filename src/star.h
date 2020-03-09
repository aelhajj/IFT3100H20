#ifndef STAR_H
#define STAR_H

#include "primitives/square.h"
#include "primitives/triangle.h"
#include "composedShape.h"
#include "primitives/circle.h"

class Star : public ComposedShape {
public:
    Star(int x, int y, int width, int height, int _stroke, ofColor _fill, ofColor _contour);

    Star();

    void update() {}

};


#endif