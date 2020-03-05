

#include "circle.h"

Circle::Circle(int _posX, int _posY, int _width, int _height, int _thickness, 
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


void Circle::setRadius(int _r)
{
    r = _r;
}
int Circle::getRadius()
{
    return r;
}
 /*       
void Circle::translate(int _posX, int _posY)
{
    cout << "le cercle se deplace de " << _posX << " en X et de " << _posY << " en Y\n";
    position_x += _posX;
    position_y += _posY;
}


void Circle::zoomIn() {
        scale += 0.25;
    }

void Circle::zoomOut() {
        if (scale > 0.25)
            scale -= 0.25;
    }

void Circle::rotate() {
        rotation += 5;
    }

       // Primitive* copy();*/

Circle::~Circle() {};
        //isfilled