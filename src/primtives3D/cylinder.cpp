
#include "cylinder.h"

Cylinder::Cylinder(float _posX, float _posY, float _width, float _height, ofColor &_fill_Color) {
    position_x = _posX;
    position_y = _posY;
    width = _width;
    height = _height;

    cylinder.set(width * .7, height * 2.2);
    cylinder.setPosition(-_width * .5 + _width * 2 / 4.f, _height * 1.1 / 6.f, 0);

    boundBox.setScale(width / 4);
    boundBox.setPosition(-_width * .5 + _width * 2 / 4.f, _height * 1.1 / 6.f, 0);
    type = SceneObjectType3D::cylinder;

    //texture.load(texture_img);
    //texture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
}

Cylinder::Cylinder() {
    //r = 100;
    type = SceneObjectType3D::cylinder;
}

void Cylinder::setTexture(ofImage imageTexture) {
    texture = imageTexture;

    texture.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

    textureMode = true;
}

void Cylinder::draw() {
    ofFill();
    ofSetColor(fillColor);

    if (textureMode)
        texture.getTexture().bind();

    if (is_mesh_mode) {
        cylinder.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        cylinder.transformGL();
        getMeshes();

        cylinder.restoreTransformGL();

        if (bottom_mesh.getNumNormals() > 0) // not null
        {
            ofPushMatrix();
            rotate();
            if (is_animate) {
                ofPushMatrix();
                ofTranslate(bottom_mesh.getNormal(0) * cylinder.getHeight() * .8);
                ofRotateDeg(sin(ofGetElapsedTimef() * 5) * RAD_TO_DEG, 1, 0, 0);
                bottom_mesh.drawWireframe();
                top_mesh.drawWireframe();
                ofPopMatrix();
                ofPushMatrix();
                ofTranslate(body_mesh.getNormal(0) * cos(ofGetElapsedTimef()) * 50);
                ofRotateDeg((cos(ofGetElapsedTimef() * 6) + 1) * .5 * 360, 1, 0, 0);
                body_mesh.drawWireframe();
                ofPopMatrix();
            } else {
                body_mesh.drawWireframe();
                bottom_mesh.drawWireframe();
                top_mesh.drawWireframe();
            }

            ofPopMatrix();
        }

    } else {
        ofPushMatrix();
        ofNoFill();
        rotate();
        cylinder.setMode(OF_PRIMITIVE_TRIANGLES);
        cylinder.draw();
        ofPopMatrix();
    }
    if (show_box) {
        ofNoFill();
        boundBox.draw();
    }

    if (textureMode) {
        texture.getTexture().unbind();
        cylinder.mapTexCoordsFromTexture(texture.getTexture());
    }
}

void Cylinder::update() {
    cylinder.set(width * 5.75, height * 5.75);
}


void Cylinder::getMeshes() {
    bottom_mesh = cylinder.getBottomCapMesh();
    body_mesh = cylinder.getCylinderMesh();
    top_mesh = cylinder.getTopCapMesh();
}

void Cylinder::translate(float x, float y, float z) {
    position_x += x;
    position_y += y;
    position_z += z;
    cylinder.setPosition((-width * .5 + width * 2 / 4.f) + position_x, (height * 1.1 / 6.f) + position_y,
                         (2 / 4.f * 0.5) + position_z);
}

void Cylinder::rotate() {
    if (is_rotating) {
        ofRotateDeg(sin(ofGetElapsedTimef() * 5) * RAD_TO_DEG, 10, 1, 1);
        ofRotateDeg(cos(ofGetElapsedTimef() * 5) * RAD_TO_DEG, 1, 10, 10);
    }
}

Cylinder::~Cylinder() {};
