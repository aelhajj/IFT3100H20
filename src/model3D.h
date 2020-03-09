#ifndef MODEL3D_H
#define MODEL3D_H

#pragma once

#include "sceneObject3D.h"
#include <cmath>
#include <string>
#include "ofxAssimpModelLoader.h"

// Classe de gestion des modèles importer en 3D. Section 4.3
class Model3D : public SceneObject3D {
public:

    Model3D(std::string _file_name);

    Model3D();

    void draw();

    void update();

    void getFileExtension();

    ~Model3D();


    ofxAssimpModelLoader model3D;
    ofNode boundBox;

    std::string file_name;
    std::string file_extension;


};

#endif
