
#include "renderer.h"
#include "histogram.h"


void Renderer::setup() {

    cam.setPosition(1000, 1000, 0);
    cam.setDistance(1000);
    ofSetBackgroundColor(31);

    // Interface de image

    ImageStruct *image = new ImageStruct;
    cout << "Avant image load" << endl;
    image->image.load("agaragar.jpg");
    cout << "Apres image load" << endl;
    image->position_x = 0;
    image->position_y = 0;
    image->width = image->image.getWidth();
    image->height = image->image.getHeight();
    cout << endl << endl << "Renderer::setup()" << endl;

    images.push_back(image);
    objects.push_back(image);
    ofColor test(44, 44, 44);
    ofColor test2(54, 66, 66);


    offset_vertical = 32;
    offset_horizontal = 32;

    viewHist = false;

     //Poin *point = new Poin(500., 500., 200., 200., 40., test2, test);
    // Rectangle *rect = new Rectangle(700., 300., 200., 200., 40., test2, test);
    // Line *ligne = new Line(500., 500., 200., 200., 40., test2, test);
    // Triangle *triang = new Triangle(800., 800., 200., 200., 40., test2, test);
    // objects.push_back(circle);
   // objects.push_back(rect);
   // objects.push_back(ligne);
   // objects.push_back(triang);

    // redimensionner la fenêtre selon la résolution de l'image
    ofSetWindowShape(screen_width, screen_height);


}

void Renderer::draw() {

    //cam.begin();
    // afficher l'image sur toute la surface de la fenêtre d'affichage
    for (SceneObject *obj : objects) {
        ofPushMatrix();
        //  ofTranslate(image.width / 2, image.heigth / 2, 0);
        //  image.image.setAnchorPercent(0.5f, 0.5f);
        obj->draw();
        ofPopMatrix();
    }

    if (is_mouse_button_pressed) {
        // dessiner la zone de sélection
        draw_zone(
                mouse_press_x,
                mouse_press_y,
                mouse_current_x,
                mouse_current_y);
    } else {
        if (!croping_zone.empty()) {
            draw_zone(
                    croping_zone[0],
                    croping_zone[1],
                    croping_zone[2],
                    croping_zone[3]);
        }
    }

    if (viewHist) {
        ofPushMatrix();
        ofTranslate(0, 100);
        draw_histogram();
        ofPopMatrix();
    }

    //cam.end();
    // dessiner le curseur
    //draw_cursor(mouse_current_x, mouse_current_y);

}

void Renderer::draw_zone(float x1, float y1, float x2, float y2) const {
    float x2_clamp = min(max(0.0f, x2), (float) ofGetWidth());
    float y2_clamp = min(max(0.0f, y2), (float) ofGetHeight());

    ofSetLineWidth(radius);
    ofSetColor(255);
    ofNoFill();
    ofDrawRectangle(x1, y1, x2_clamp - x1, y2_clamp - y1);
    ofFill();
    ofDrawEllipse(x1, y1, radius, radius);
    ofDrawEllipse(x1, y2_clamp, radius, radius);
    ofDrawEllipse(x2_clamp, y1, radius, radius);
    ofDrawEllipse(x2_clamp, y2_clamp, radius, radius);
}

// fonction qui dessine un curseur
// void Renderer::draw_cursor(float x, float y) const
// {
//   float length = 10.0f;
//   float offset = 5.0f;
//
//   ofSetLineWidth(2);
//   ofDrawLine(x + offset, y, x + offset + length, y);
//   ofDrawLine(x - offset, y, x - offset - length, y);
//   ofDrawLine(x, y + offset, x, y + offset + length);
//   ofDrawLine(x, y - offset, x, y - offset - length);
// }


void Renderer::draw_histogram() {
    Histogram hist;
    hist.setup(images.at(0)->image);
    hist.update();
    hist.draw();
}

void Renderer::add_primitive(SceneObjectType type) {
    SceneObject *newShape;
    switch (type) {
        case SceneObjectType::circle:
            newShape = new Circle();

            break;

        case SceneObjectType::point:
            newShape = new Poin();
            break;
        
        case SceneObjectType::line:
            newShape = new Line();
            break;

        case SceneObjectType::rectangle:
            newShape = new Rectangle();
            break;
        
        case SceneObjectType::triangle:
            newShape = new Triangle();
            break;

        default:
            break;
    }

    int x1 = mouse_press_x <= mouse_current_x ? mouse_press_x : mouse_current_x;
    int x2 = mouse_press_x >= mouse_current_x ? mouse_press_x : mouse_current_x;
    int y1 = mouse_press_y <= mouse_current_y ? mouse_press_y : mouse_current_y;
    int y2 = mouse_press_y >= mouse_current_y ? mouse_press_y : mouse_current_y;

    newShape->width = x2 - x1;
    newShape->height = y2 - y1;

    newShape->position_x = x1 + newShape->width / 2;
    newShape->position_y = y1 + newShape->height / 2;

    newShape->thickness = stroke_size;
    newShape->borderColor = stroke_color;
    newShape->fillColor = fill_color;

    newShape->update();

    objects.push_back(newShape);

}

void Renderer::update() {
    ofSetBackgroundColor(background_color);
    if (sceneObjectSelected != nullptr) {
        if (sceneObjectSelected->type == SceneObjectType::image)
            imageSelected = (ImageStruct *) sceneObjectSelected;
            //else if (sceneObjectSelected->type == SceneObjectType::circle)
        else {
            sceneObjectSelected->borderColor = stroke_color;
            sceneObjectSelected->fillColor = fill_color;
            sceneObjectSelected->thickness = stroke_size;
            //cout << (int)sceneObjectSelected->thickness << endl;
        }
    }

}

void Renderer::reset() {
    // int buffer_count = objects.size;
    // for(auto &obj : objects)
    // {
    //     if (obj ->type != SceneObjectType::image)

    // }

}
