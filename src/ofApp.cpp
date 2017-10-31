#include "ofApp.h"

//~~Let's get messy~~//

//Bubble constructor
Bubble::Bubble() {
	position.x = ofRandom((ofGetWidth() - 50.0));
	position.y = 0.0;
	color.r = 67;
	color.g = 199;
	color.b = 255;
	radius = 30;
}

//determines whether bubble stays or goes
bool Bubble::isRemoved(ofxCvGrayscaleImage refImg, ofPixels pixels) {
	int movementAmt = 0;
	pixels = refImg.getPixels();
	for (int y = position.y - (radius / 2); y < position.y + (radius / 2); y++) {
		for (int x = position.x - (radius / 2); x < position.x + (radius / 2); x++) {
			if (pixels.getColor(y + x).getBrightness() > 100) {
				movementAmt++;
			}
		}
	}
	if (movementAmt > 5) {
		return true;
	}
	else {
		return false;
	}
}


//--------------------------------------------------------------
void ofApp::setup() {
	camWidth = ofGetWidth();
	camHeight = ofGetHeight();

	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(30);
	vidGrabber.initGrabber(ofGetWidth(), ofGetHeight());

	previous.allocate(ofGetWidth(), ofGetHeight());
	current.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {
	colorImg.setFromPixels(vidGrabber.getPixelsRef());
	previous = colorImg;
	vidGrabber.update();
	colorImg.setFromPixels(vidGrabber.getPixelsRef());
	current = colorImg;
	difference.absDiff(current, previous);
	difference.threshold(30);

	for (int i = 0; i < bubbles.size(); ++i) {
		if (bubbles[i].isRemoved(difference, pixels) == true) {
			bubbles.erase((bubbles.begin() + i));
			--i; //make sure you don't skip over a bubble
		}
		else {
			bubbles[i].position.y += 3;
		}
	}

	for (int i = 0; i < bubbles.size(); ++i) {
		if (bubbles[i].position.y > ofGetHeight()) {
			bubbles.erase((bubbles.begin() + i));
		}
	}
	updated = true;
}

//--------------------------------------------------------------
void ofApp::draw() {
	vidGrabber.draw(0,0);

	int frameNum = ofGetFrameNum();
	if (frameNum % 30 == 0) {
		Bubble bubble;
		ofDrawCircle(bubble.position.x, bubble.position.y, bubble.radius);
		ofSetColor(bubble.color);
		ofNoFill();
		//add bubble to bubbles vector
		bubbles.push_back(bubble);
	}

	if (updated == true) {
		for (int i = 0; i < bubbles.size(); ++i) {
			ofDrawCircle(bubbles[i].position.x, bubbles[i].position.y, bubbles[i].radius);
		}
	}
}

//Spacebar clears the bubbles if you feel like it
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		bubbles.clear();
	}
}

