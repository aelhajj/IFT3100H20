

#include "ofMain.h"
#include <tuple>

class Primitive {
    public:
        Primitive(float _posX, float _posY, float _width, float _height, float _thickness, ofColor& fill_Color, ofColor& border_Color);

        static int prim_size;
        
        virtual void draw(){}

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

        bool isSelected(float _posX, float _posY);

        void setShape(float _posX, float _posY, float _setX, float _setY);

        void translate(float _posX, float _posY);

        bool operator==(Primitive primitive);

        Primitive* copy();

        ~Primitive();

        ofColor fillColor;
        ofColor borderColor;

        float position_x;
        float position_y;
        float width;
        float height;
        float thickness;

};