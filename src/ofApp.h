#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvGrayscaleImage.h"

class Bubble {
public:
	Bubble();

	ofVec2f position;
	ofColor color;
	int radius;

	bool isRemoved(ofxCvGrayscaleImage refImg, ofPixels pixels);
};

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	vector<Bubble> bubbles;
	bool updated;

	ofVideoGrabber vidGrabber;
	int camWidth, camHeight;

	ofxCvColorImage colorImg;
	ofxCvGrayscaleImage current, previous, difference;

	ofPixels pixels;
};