#include "star.h"

Star::Star(int x, int y, int width, int height,int _stroke, ofColor _fill, ofColor _contour)
{
    //ComposedShape(x,y,width,height);
    int square_x = x + (width / 3);
    int square_y = y + (height / 3);
    int square_width = (width / 3);
    int square_height = (height / 3);

    //ofColor test(40,40,40);

    Square* square = new Square(square_x, square_y, square_width, square_height, _stroke, _fill, _contour);

    Circle* circle = new Circle(square_x,square_y+square_height/2, square_width, square_height/2, _stroke, _fill, _contour);

    Circle* circle2 = new Circle(square_x,square_y-square_height/2, square_width, square_height/2, _stroke, _fill, _contour);

    Circle* circle3 = new Circle(square_x+square_width/2,square_y, square_width, square_height/2, _stroke, _fill, _contour);

    Circle* circle4 = new Circle(square_x-square_width/2,square_y, square_width, square_height/2, _stroke, _fill, _contour);

    primitives.push_back(square);

    primitives.push_back(circle);

    primitives.push_back(circle2);

    primitives.push_back(circle3);

    primitives.push_back(circle4);

    type = SceneObjectType::quatrefoil;

}

Star::Star() {
    int _stroke = 0;
    ofColor _fill(100, 100, 100);
    ofColor _contour(100, 100, 100);

    int x = 300;
    int y = 300;
    int width = 300;
    int height = 300;
    //ComposedShape(x,y,width,height);
    int square_x = x + (width / 3);
    int square_y = y + (height / 3);
    int square_width = (width / 3);
    int square_height = (height / 3);

    //ofColor test(40,40,40);

    Square* square = new Square(square_x, square_y, square_width, square_height, _stroke, _fill, _contour);

    Circle* circle = new Circle(square_x,square_y+square_height/2, square_width, square_height/2, _stroke, _fill, _contour);

    Circle* circle2 = new Circle(square_x,square_y-square_height/2, square_width, square_height/2, _stroke, _fill, _contour);

    Circle* circle3 = new Circle(square_x+square_width/2,square_y, square_width, square_height/2, _stroke, _fill, _contour);

    Circle* circle4 = new Circle(square_x-square_width/2,square_y, square_width, square_height/2, _stroke, _fill, _contour);

    primitives.push_back(square);

    primitives.push_back(circle);

    primitives.push_back(circle2);

    primitives.push_back(circle3);

    primitives.push_back(circle4);

    type = SceneObjectType::quatrefoil;
}
