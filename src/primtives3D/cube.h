#ifndef CUBE_H
#define CUBE_H

#include "primitive3D.h"
#include <cmath>

class Cube : public Primitive3D {
public:
    Cube(float _posX, float _posY, float _width, float _height, ofColor &fill_Color);

    Cube();

    void draw();

    void setPosition(float _posX, float _posY);

    void update();

    void translate(float x, float y, float z);

    void getMeshes();

    void rotate();


    ~Cube();

    ofBoxPrimitive cube;
    ofNode boundBox;

    ofVboMesh cube_sides[ofBoxPrimitive::SIDES_TOTAL];
    
    

};

#endif
