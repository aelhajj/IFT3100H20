
#pragma once
#include "renderer.h"
#include "ofxHistogram.h"

class Histogram
{
    public:
        // pour histogramme :
        ofxHistogram histogram;
        ofPolyline line;

            
        ofxCvColorImage rgb; //, hsv
        ofxCvGrayscaleImage r, g, b;
        //ofxCvGrayscaleImage h, s, v;

        int image_width = 256;
        int image_height = 256;

       //  rgb.allocate(image_width, image_height);

       //  r.allocate(image_width, image_height);
       //  g.allocate(image_width, image_height);
       //  b.allocate(image_width, image_height);

        vector<float> histogramR, histogramG, histogramB;
        vector<float> histogramH, histogramS, histogramV;


void drawHistogram(vector<float> & h) 
{
    ofPolyline line;
    ofSetLineWidth(3);
    for (int i=0; i<h.size(); i++) {
        float x = ofMap(i, 0, h.size(), 0, 320);
        float y = ofMap(h[i], 0, 0.3, 240, 0);
        ofPoint pt;
        pt.set(x, y);
        line.addVertex(pt);
    }
    line.draw();
}

void makeHistogram(ofImage image_source)
{
    image_source.update();

    rgb.setFromPixels(image_source.getPixels());

    // get separate red, green, blue channels
    r.setFromPixels(rgb.getPixels().getChannel(0));
    g.setFromPixels(rgb.getPixels().getChannel(1));
    b.setFromPixels(rgb.getPixels().getChannel(2));

    // get histograms
    histogramR = histogram.getHistogram(r, 30); // 30 bins

    ofSetColor(255, 0, 0);
    r.draw(0, 0);
    drawHistogram(histogramR);
    
    ofTranslate(image_width, 0);

    ofSetColor(0, 255, 0);
    histogramG = histogram.getHistogram(g, 30);
    g.draw(0, 0);
    drawHistogram(histogramG);
    
    ofTranslate(image_width, 0);
    
    ofSetColor(0, 0, 255);
    histogramB = histogram.getHistogram(b, 30);
    b.draw(0, 0);
    drawHistogram(histogramB);


    ofTranslate(-2*image_width, -image_height);
    ofDrawBitmapString("red", 0, 15);
    ofDrawBitmapString("green", image_width, 15);
    ofDrawBitmapString("blue", 2*image_width, 15);

    ofSetColor(255, 255, 255);
    
}

};
