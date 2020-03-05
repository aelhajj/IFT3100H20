#pragma once

#include "ofMain.h"
#include <vector>
#include "sceneObject.h"


class ImageStruct : public SceneObject {
public:
    ofImage image;
    //float position_x = 0;
    //float position_y = 0;
//    float width = 900;
//    float heigth = 900;


/*
    void translate(int x, int y) {
        position_x += x;
        position_y += y;
    }
    void zoomIn() {
        scale += 0.25;
    }

    void zoomOut() {
        if (scale > 0.25)
            scale -= 0.25;
    }

    void rotate() {
        rotation += 5;
    }*/

    void draw() {
        //ofTranslate(width / 2, height / 2, 0);
        //setAnchorPercent(0.5f, 0.5f);
        //cout << "Image drawn at " << position_x << ":" << position_y << " with size " << width << "x" << height << endl;
        ofRotate(rotation);
        ofScale(scale);
        image.draw(position_x,
                   position_y,
                   width,
                   height);
        
    }

};
