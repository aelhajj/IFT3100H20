#include "model3D.h"


Model3D::Model3D(std::string _file_name) {
    model3D.loadModel(_file_name);
    file_name = _file_name;

}

Model3D::Model3D() {
    model3D.loadModel("teapot.obj");
    file_name = "teapot.obj";
}

void Model3D::draw() {
    model3D.setRotation(0, 0, 0, 0, 0);
    model3D.setScale(1, 1, 1);
    model3D.drawFaces();
}

void Model3D::update() {
}

void Model3D::getFileExtension() {
    file_extension = file_name.substr(file_name.find_last_of(".") + 1);
    if (file_extension == "dae")
        ofLog() << "Current file : dae";

    if (file_extension == "3ds")
        ofLog() << "Current file : 3ds";

    if (file_extension == "ply")
        ofLog() << "Current file : ply" << endl;
    // useMesh();

    if (file_extension == "obj")
        ofLog() << "Current file : obj" << endl;
}

// ofxAssimpModelLoader model3D;
// ofNode boundBox;

