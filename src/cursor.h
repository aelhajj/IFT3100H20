
#pragma once

#include "renderer.h"

class Cursor {
public:
    virtual void onMouseMoved(int x, int y) = 0;

    virtual void onMouseDragged(int x, int y) = 0;

    virtual void onMousePressed(int x, int y) = 0;

    virtual void onMouseReleased(int x, int y) = 0;

    virtual void drawCursor() = 0;
};


class CropCursor : public Cursor {
public:
    CropCursor(Renderer *r) {
        renderer = r;
    }

    void onMouseMoved(int x, int y) {
        renderer->mouse_current_x = x;
        renderer->mouse_current_y = y;
    }

    void onMouseDragged(int x, int y) {
        renderer->mouse_current_x = x;
        renderer->mouse_current_y = y;
    }

    void onMousePressed(int x, int y) {

        renderer->is_mouse_button_pressed = true;
        renderer->croping_zone.clear();

        renderer->mouse_current_x = x;
        renderer->mouse_current_y = y;

        renderer->mouse_press_x = x;
        renderer->mouse_press_y = y;
    }

    void onMouseReleased(int x, int y) {
        renderer->is_mouse_button_pressed = false;
        if (y > 100) {
            renderer->croping_zone.push_back(renderer->mouse_press_x);
            renderer->croping_zone.push_back(renderer->mouse_press_y);
            renderer->croping_zone.push_back(renderer->mouse_current_x);
            renderer->croping_zone.push_back(renderer->mouse_current_y);
        }

        renderer->mouse_current_x = x;
        renderer->mouse_current_y = y;
    }

    void drawCursor() {
        float x = renderer->mouse_current_x;
        float y = renderer->mouse_current_y;
        float length = 10.0f;
        float offset = 5.0f;

        ofSetLineWidth(2);
        ofDrawLine(x + offset, y, x + offset + length, y);
        ofDrawLine(x - offset, y, x - offset - length, y);
        ofDrawLine(x, y + offset, x, y + offset + length);
        ofDrawLine(x, y - offset, x, y - offset - length);
    }

private:
    Renderer *renderer;
};

class NormalCursor : public Cursor {
public:
    NormalCursor(Renderer *r) {
        renderer = r;
        image.load("handCursor.png");
    }

    void onMouseMoved(int x, int y) {
        renderer->mouse_current_x = x;
        renderer->mouse_current_y = y;
        last_frame_x = x;
        last_frame_y = y;
    }

    void onMouseDragged(int x, int y) {
        if (isSceneObjectSelected) {
            float delta_x = x - last_frame_x;
            float delta_y = y - last_frame_y;

            sceneObjectSelected->translate(delta_x, delta_y);

        }
        last_frame_x = x;
        last_frame_y = y;

    }

    void onMousePressed(int x, int y) {
        for (auto &obj: renderer->objects) {
            obj->info();
            if (x >= obj->position_x &&
                x <= (obj->width + obj->position_x) &&
                y >= obj->position_y &&
                y <= (obj->height + obj->position_y)) {
                //  cout<< "obj selected because "<< x << " is bigger than " << obj->position_x << " but smaller than " << obj->position_x + obj->width << endl;
                sceneObjectSelected = obj;
                isSceneObjectSelected = true;

            }
        }
    }

    void onMouseReleased(int x, int y) {
        isSceneObjectSelected = false;
    }

    void drawCursor() {
        image.draw(ofGetMouseX() - 10, ofGetMouseY() - 10, 50, 45);
    }

private:
    int last_frame_x;
    int last_frame_y;
    bool isSceneObjectSelected = false;
    SceneObject *sceneObjectSelected;
    ofImage image;
    Renderer *renderer;
};

class ZoomInCursor : public Cursor {
public:
    ZoomInCursor(Renderer *r) {
        renderer = r;
        image.load("ZoomIn.png");
    }

    void onMouseMoved(int x, int y) {
        renderer->mouse_current_x = x;
        renderer->mouse_current_y = y;
    }

    void onMouseDragged(int x, int y) {


    }

    void onMousePressed(int x, int y) {
        for (auto &obj: renderer->objects) {

            if (x > obj->position_x &&
                x < (obj->width + obj->position_x) &&
                y > obj->position_y &&
                y < (obj->height + obj->position_y)) {
                sceneObjectSelected = obj;
                sceneObjectSelected->zoomIn();
            }
        }
    }

    void onMouseReleased(int x, int y) {

    }

    void drawCursor() {
        image.draw(ofGetMouseX() - 10, ofGetMouseY() - 10, 50, 45);
    }

private:
    Renderer *renderer;
    SceneObject *sceneObjectSelected;

    ofImage image;
};


class ZoomOutCursor : public Cursor {
public:
    ZoomOutCursor(Renderer *r) {
        renderer = r;
        image.load("ZoomOut.png");
    }

    void onMouseMoved(int x, int y) {
        renderer->mouse_current_x = x;
        renderer->mouse_current_y = y;
    }

    void onMouseDragged(int x, int y) {

    }

    void onMousePressed(int x, int y) {
        for (auto &obj: renderer->objects) {

            if (x > obj->position_x &&
                x < (obj->width + obj->position_x) &&
                y > obj->position_y &&
                y < (obj->height + obj->position_y)) {
                sceneObjectSelected = obj;
                sceneObjectSelected->zoomOut();
            }
        }
    }

    void onMouseReleased(int x, int y) {

    }

    void drawCursor() {
        image.draw(ofGetMouseX() - 10, ofGetMouseY() - 10, 50, 45);
    }

private:
    Renderer *renderer;
    SceneObject *sceneObjectSelected;
    ofImage image;
};


class RotationCursor : public Cursor {
public:
    RotationCursor(Renderer *r) {
        renderer = r;
        image.load("rotate.png");
    }

    void onMouseMoved(int x, int y) {
        renderer->mouse_current_x = x;
        renderer->mouse_current_y = y;
    }

    void onMouseDragged(int x, int y) {

    }

    void onMousePressed(int x, int y) {
        for (auto &obj: renderer->objects) {
            if (x > obj->position_x &&
                x < (obj->width + obj->position_x) &&
                y > obj->position_y &&
                y < (obj->height + obj->position_y)) {
                sceneObjectSelected = obj;
                sceneObjectSelected->rotate();
            }
        }
    }

    void onMouseReleased(int x, int y) {

    }

    void drawCursor() {
        image.draw(ofGetMouseX() - 10, ofGetMouseY() - 10, 50, 45);
    }

private:
    Renderer *renderer;
    SceneObject *sceneObjectSelected;
    ofImage image;
};
