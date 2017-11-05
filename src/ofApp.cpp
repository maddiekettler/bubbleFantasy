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


//--------------------------------------------------------------
void ofApp::setup() {
	//Camera stuff
	camWidth = 1280;
	camHeight = 720;

	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(30);
	vidGrabber.initGrabber(camWidth, camHeight);

	colorImg.allocate(camWidth, camHeight);
	previous.allocate(camWidth, camHeight);
	current.allocate(camWidth, camHeight);
	difference.allocate(camWidth, camHeight);
	forDrawing.allocate(camWidth, camHeight);
	forDrawing.setFromPixels(vidGrabber.getPixelsRef());

	bubblePop1.load("pop1.wav");
	bubblePop2.load("pop2.wav");
	bubblePop2.setMultiPlay(true);
	bubblePop2.setMultiPlay(true);
}

//--------------------------------------------------------------
void ofApp::update() {
	// forDrawing.setFromPixels(vidGrabber.getPixelsRef());
	colorImg.setFromPixels(vidGrabber.getPixelsRef());
	previous = colorImg;
	vidGrabber.update();
	colorImg.setFromPixels(vidGrabber.getPixelsRef());
	current = colorImg;
	difference.absDiff(current, previous);
	difference.threshold(30);
    difference.mirror(false, true);
    difference.flagImageChanged();

	int randNum = (int)ofRandom(0, 2);

	for (int i = 0; i < bubbles.size(); ++i) {
        int movementAmt = 0;
        pixels = difference.getPixels();
        float leftX = bubbles[i].position.x - (bubbles[i].radius / 2);
        float topY = bubbles[i].position.y - (bubbles[i].radius / 2);
        float rightX = bubbles[i].position.x + (bubbles[i].radius / 2);
        float bottomY = bubbles[i].position.y + (bubbles[i].radius / 2);
        for (int y = topY; y < bottomY; y++) {
            for (int x = leftX; x < rightX; x++) {
                if(pixels.getColor(y, x).getLightness() > 150) {
                    movementAmt++;
                }
            }
        }

		if (movementAmt > 10) {
			bubbles.erase((bubbles.begin() + i));
			bubblePop2.play();
			--i; //make sure you don't skip over a bubble
		}
		else {
			bubbles[i].position.y += 3;
		}
	}

	// erase the bubble if it falls off of the screen
	for (int i = 0; i < bubbles.size(); ++i) {
		if (bubbles[i].position.y > camHeight + 50) {
			bubbles.erase((bubbles.begin() + i));
		}
	}
	
	updated = true;
}

//--------------------------------------------------------------
void ofApp::draw() {
	forDrawing.setFromPixels(vidGrabber.getPixelsRef());
	forDrawing.mirror(false, true);
	forDrawing.draw(0, 0);
	
	int frameNum = ofGetFrameNum();
	if (frameNum % 30 == 0) {
		Bubble bubble;
		ofDrawCircle(bubble.position.x, bubble.position.y, bubble.radius);
		ofSetColor(bubble.color);
		ofSetLineWidth(5);
		ofNoFill();
		//add bubble to bubbles vector
		bubbles.push_back(bubble);
	}

	if (updated == true) {
		for (int i = 0; i < bubbles.size(); ++i) {
			ofDrawCircle(bubbles[i].position.x, bubbles[i].position.y, bubbles[i].radius);
		}
	}
//    difference.draw(0,0, 320, 240);
}


// Spacebar clears the bubbles
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		bubbles.clear();
	}
}
