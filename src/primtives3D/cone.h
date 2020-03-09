#ifndef CONE_H
#define CONE_H

#include "primitive3D.h"
#include <cmath>

class Cone : public Primitive3D {
public:
    Cone(float _posX, float _posY, float _width, float _height, ofColor &fill_Color);

    Cone();

    void draw();

    void setPosition(float _posX, float _posY);

    void update();

    void translate(float x, float y, float z);

    void getMeshes();

    void rotate();

    ~Cone();

    ofConePrimitive cone;
    ofNode boundBox;
    ofVboMesh bottom_mesh;
    ofVboMesh body_mesh;
    ofMaterial material;
    vector<ofMeshFace> triangles;
    

};

#endif
