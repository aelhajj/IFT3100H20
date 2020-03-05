

#include "circle.h"

Circle::Circle(float _posX, float _posY, float _width, float _height, float _thickness, 
            ofColor& _fill_Color, ofColor& _border_Color) :
            Primitive(_posX, _posY, _width, _height, _thickness, _fill_Color, _border_Color)
{
    r = width/2;
    prim_size++;
}

void Circle::draw()
{
    ofFill();
    ofSetColor(fillColor);
    ofSetLineWidth(0);
    ofSetCircleResolution(100);
    ofDrawCircle(position_x, position_y, r);
    
    ofNoFill();
    ofSetColor(borderColor);
    ofSetLineWidth(thickness);
    ofSetCircleResolution(100);
    ofDrawCircle(position_x, position_y, r);

    ofSetColor(255, 255, 255);
}


void Circle::setRadius(float _r)
{
    r = _r;
}
float Circle::getRadius()
{
    return r;
}
        //bool isSelected(float _posX, float _posY);

        //void setShape(float _posX, float _posY, float _setX, float _setY);

        //void translate(float _posX, float _posY);

/*bool operator==(Primitive primitive)
{
    //todo.
}*/

       // Primitive* copy();

Circle::~Circle() {};

        float r;
        //isfilled