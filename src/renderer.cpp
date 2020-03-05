
#include "renderer.h"
#include "histogram.h"


void Renderer::setup() {

    cam.setPosition(1000, 1000, 0);
    cam.setDistance(1000);
    ofSetBackgroundColor(31);

    // Interface de image

    ImageStruct *image = new ImageStruct;

    image->image.load("agaragar.jpg");

    image->position_x = 0;
    image->position_y = 0;
    image->width = image->image.getWidth();
    image->height = image->image.getHeight();

    images.push_back(image);
    objects.push_back(image);
    ofColor test(44, 44, 44);
    ofColor test2(54, 66, 66);


    offset_vertical = 32;
    offset_horizontal = 32;

    viewHist = false;

    Circle *circle = new Circle(300., 300., 200., 200., 40., test2, test);
    objects.push_back(circle);

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
