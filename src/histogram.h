#pragma once

#include "ofxHistogram.h"
#include "ofMain.h"

// Classe pour l'histogramme, utilise ofxHistogram, section 1.4
class Histogram {
public:
    void setup(ofImage image);

    void update();

    void draw();

    void drawHistogram(vector<float> &h);

    int width;
    int height;
    ofImage image;

    ofxCvColorImage rgb, hsv;
    ofxCvGrayscaleImage r, g, b;
    ofxCvGrayscaleImage h, s, v;

    vector<float> histogramR, histogramG, histogramB;
    vector<float> histogramH, histogramS, histogramV;

    ofxHistogram histogram;
};
