#include "cone.h"

Cone::Cone(float _posX, float _posY, float _width, float _height, ofColor &_fill_Color) {
    position_x = _posX;
    position_y = _posY;
    width = _width;
    height = _height;
    
    cone.set(width*.75, height*2.2);
    cone.setPosition( -_width * .5 + _width *  2/4.f, _height *  1.1/6.f, 0);

    boundBox.setScale(width/5);
    boundBox.setPosition(-_width * .5 + _width *  2/4.f, _height *  1.1/6.f, 0);
    type = SceneObjectType3D::cone;
}

Cone::Cone() {
    type = SceneObjectType3D::cone;
}

void Cone::draw() {
    ofFill();
    ofSetColor(fillColor);
    
    if(is_mesh_mode) {
        cone.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        cone.transformGL();
        getMeshes();

        cone.restoreTransformGL();
        
        if(bottom_mesh.getNumNormals() > 0) // not null 
        {   
            ofPushMatrix();
            rotate();
            if (is_animate) {
                ofPushMatrix();
                ofTranslate(bottom_mesh.getNormal(0) * cone.getHeight()* .8);
                ofRotateDeg(sin(ofGetElapsedTimef() * 5) * RAD_TO_DEG, 1, 0, 0);
                bottom_mesh.drawWireframe();
                ofPopMatrix();
                ofPushMatrix();
                ofTranslate(body_mesh.getNormal(0) * cos(ofGetElapsedTimef()) * 50);
                ofRotateDeg((cos(ofGetElapsedTimef() * 6) + 1)*.5 * 360, 1, 0, 0);
                body_mesh.drawWireframe();
                ofPopMatrix();
            }
            else {
                body_mesh.drawWireframe();
                bottom_mesh.drawWireframe();
            }
            
            ofPopMatrix();
        } 
        
    } else {
        ofPushMatrix();
        ofNoFill();
        rotate();
        cone.setMode(OF_PRIMITIVE_TRIANGLES);
        cone.draw();
        ofPopMatrix();
    }
       
    if(show_box) {
        ofNoFill();
        boundBox.draw();
    }
        
}

void Cone::update() {
    cone.set(width *0.75, height*1.75);
}

void Cone::getMeshes() {
    bottom_mesh = cone.getCapMesh();
    body_mesh = cone.getConeMesh();
}

void Cone::translate(float x, float y, float z) {
    position_x += x;
    position_y += y;
    position_z += z;
    cone.setPosition((-width * .5 + width *  2/4.f) + position_x, (height *  1.1/6.f) + position_y, (2/4.f * 0.5) +position_z); 
}

void Cone::rotate() {
    if(is_rotating) {
        ofRotateDeg(sin(ofGetElapsedTimef() * 5) * RAD_TO_DEG, 10, 1, 1);
        ofRotateDeg(cos(ofGetElapsedTimef() * 5) * RAD_TO_DEG, 1, 10, 10);
    }
}

Cone::~Cone() {};
