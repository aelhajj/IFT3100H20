

#include "primitive.h"

Primitive::Primitive(int _posX, int _posY, int _width, int _height, int _thickness, ofColor& _fillColor, ofColor& _borderColor)
{
    position_x = _posX;
    position_y = _posY;
    thickness = _thickness;
    fillColor = _fillColor;
    borderColor = _borderColor;
    width = _width;
    height = _height;
}

ofColor Primitive::getFillColor()
{
    return fillColor;
}

void Primitive::setFillColor(ofColor _fillColor)
{
    fillColor = _fillColor;
}

ofColor Primitive::getBorderColor()
{
    return borderColor;
}
void Primitive::setBorderColor(ofColor _borderColor)
{
    borderColor = _borderColor;
}

int Primitive::getThickness() 
{
    return thickness;
}
void Primitive::setThickness(int _thickness)
{
    thickness = _thickness;
}
/*
tuple<float, float> Primitive::getPosition() 
{
    return make_tuple(position_x, position_y);
}
void Primitive::setPosition(float _posX, float _posY)
{
    position_x = _posX;
    position_y = _posY;
}

float Primitive::getHeight()
{
    return height;
}
void Primitive::setHeight(float _height)
{
    height = _height;
}
float Primitive::getWidth()
{
    return width;
}
void Primitive::setWidth(float _width)
{
    width = _width;
}


bool Primitive::isSelected(float posX, float posY) 
{

}*/

//void Primitive::setShape(float posX, float posY, float setX, float setY);

//void translate(float posX, float posY);

//bool operator==(Primitive primitive);

//Primitive* copy();

Primitive::~Primitive() {}

int Primitive::prim_size = 0;