

#include "primitive.h"
#include <cmath>

class Circle: public Primitive
{
    public: 
        Circle(float _posX, float _posY, float _width, float _height, float _thickness, 
            ofColor& fill_Color, ofColor& border_Color);

        void draw();

        ofColor getFillColor();
        void setFillColor(ofColor _fillColor);

        ofColor getBorderColor();
        void setBorderColor(ofColor _borderColor);

        tuple<float, float> getPosition();
        void setPosition(float _posX, float _posY);

        float getWidth();
        void setWidth(float _width);

        float getHeight();
        void setHeight(float _height);

        float getThickness();
        void setThickness(float _thickness);

        float getRadius();
        void setRadius(float _r);

        bool isSelected(float _posX, float _posY);

        void setShape(float _posX, float _posY, float _setX, float _setY);

        void translate(float _posX, float _posY);

        bool operator==(Primitive primitive);

        Primitive* copy();

        ~Circle();

        float r;
};