#include "histogram.h"

void Histogram::setup(ofImage image) {
    image.resize(250, 200);
    this->image = image;
    this->height = image.getHeight();
    this->width = image.getWidth();
    //cout << "Histogram width: " << this->width << endl
    //     << "Histogram height: " << this->height << endl;

    rgb.allocate(width, height);
    hsv.allocate(width, height);
    r.allocate(width, height);
    g.allocate(width, height);
    b.allocate(width, height);
    h.allocate(width, height);
    s.allocate(width, height);
    v.allocate(width, height);
}

void Histogram::update() {
    rgb.setFromPixels(image.getPixels());

    // get separate red, green, blue channels
    r.setFromPixels(rgb.getPixels().getChannel(0));
    g.setFromPixels(rgb.getPixels().getChannel(1));
    b.setFromPixels(rgb.getPixels().getChannel(2));

    // convert rgb to hsv and grab each channel individually
    cvCvtColor(rgb.getCvImage(), hsv.getCvImage(), CV_BGR2HSV);
    h.setFromPixels(hsv.getPixels().getChannel(0));
    s.setFromPixels(hsv.getPixels().getChannel(1));
    v.setFromPixels(hsv.getPixels().getChannel(2));

    // get histograms
    histogramR = histogram.getHistogram(r, 30); // 30 bins
    histogramG = histogram.getHistogram(g, 30);
    histogramB = histogram.getHistogram(b, 30);
    histogramH = histogram.getHistogram(h, 30);
    histogramS = histogram.getHistogram(s, 30);
    histogramV = histogram.getHistogram(v, 30);
}

void Histogram::drawHistogram(vector<float> &h) {
    ofBeginShape();

    ofNoFill();
    ofSetLineWidth(3);
    for (int i = 0; i < h.size(); i++) {
        float x = ofMap(i, 0, h.size(), 0, this->width);
        float y = ofMap(h[i], 0, 0.3, this->height, 0);
        ofVertex(x, y);
    }
    ofEndShape();
}

void Histogram::draw() {
    ofSetColor(255, 0, 0);
    drawHistogram(histogramR);

    ofSetColor(0, 255, 0);
    drawHistogram(histogramG);

    ofSetColor(0, 0, 255);
    drawHistogram(histogramB);
    ofSetColor(255);
}
