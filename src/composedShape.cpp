#include "composedShape.h"


void ComposedShape::draw() {
    for (Primitive* prim : primitives) {
        prim->draw();
    }
}

void ComposedShape::translate(int x, int y) {
    for (Primitive* prim : primitives) {
        //cout << "aa" << endl;
        prim->translate(x, y);
    }
}
