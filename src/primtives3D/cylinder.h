#ifndef CYLINDER_H
#define CYLINDER_H

#include "primitive3D.h"
#include <cmath>

class Cylinder : public Primitive3D {
public:
    Cylinder(float _posX, float _posY, float _width, float _height, ofColor &fill_Color);

    Cylinder();

    void setTexture(ofImage imageTexture);

    void draw();

    void update();

    void translate(float x, float y, float z);

    void getMeshes();

    void rotate();


    ~Cylinder();

    ofCylinderPrimitive cylinder;
    ofNode boundBox;

    ofVboMesh bottom_mesh;
    ofVboMesh body_mesh;
    ofVboMesh top_mesh;


};

#endif
