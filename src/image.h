#pragma once

#include "ofMain.h"
#include <vector>
#include "sceneObject.h"

// Classe pour la gestion des images, hérite de SceneObject. Section 1 
class ImageStruct : public SceneObject {
public:
    ofImage image;

    ImageStruct() {
        type = SceneObjectType::image;
    }

    void update() {}

    void draw() {
        ofRotate(rotation);
        ofScale(scale);
        image.draw(position_x,
                   position_y,
                   width,
                   height);
    }


};
