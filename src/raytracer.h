#pragma once

#include "ofMain.h"
#include <vector>
#include "image.h"

class Raytracer {
public:

    ImageStruct* image = new ImageStruct();
    void setup();
    void draw();
    void static callRaytracer();


};
