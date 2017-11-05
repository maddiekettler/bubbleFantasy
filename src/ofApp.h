#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

// #define USE_TWO_SOUNDS  // uncomment to use two popping sounds instead of just one

class Bubble {
public:
	Bubble();

	ofVec2f position;
	ofColor color;
	int radius;
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

	ofxCvColorImage colorImg, forDrawing;
	ofxCvGrayscaleImage current, previous, difference;

	ofPixels pixels;

	// let there be sound
	ofSoundPlayer bubblePop1;
	ofSoundPlayer bubblePop2;
};