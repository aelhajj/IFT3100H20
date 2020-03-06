#pragma once

#include "ofMain.h"
#include <vector>
#include "sceneObject.h"


class ImageStruct : public SceneObject {
public:
    ofImage image;

    ImageStruct() {
        type = SceneObjectType::image;
    }

    void update() {}

    void draw() {
        //ofTranslate(width / 2, height / 2, 0);
        //setAnchorPercent(0.5f, 0.5f);
        ofRotate(rotation);
        ofScale(scale);
        image.draw(position_x,
                   position_y,
                   width,
                   height);

    }


};
