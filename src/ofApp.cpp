#include "ofApp.h"

/* All sounds obtained from freesound.org
pop1.wav: https://freesound.org/s/260614/
pop2.wav: https://freesound.org/s/265115/ */



//Bubble constructor
Bubble::Bubble() {
	position.x = ofRandom((ofGetWidth() - 50.0));
	position.y = 0.0;
	color.r = 67;
	color.g = 199;
	color.b = 255;
	radius = 30;
}

//--------------------------------------------------------------
void ofApp::setup() {
	// Camera setup
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

	// Sound setup
	bubblePop1.load("pop1.wav");
	bubblePop2.load("pop2.wav");
	bubblePop2.setMultiPlay(true);
	bubblePop2.setMultiPlay(true);
}

//--------------------------------------------------------------
void ofApp::update() {
	// get CV color image from vidGrabber
	colorImg.setFromPixels(vidGrabber.getPixelsRef());
	// grayscale color image
	previous = colorImg;
	// update to get next frame from vidGrabber
	vidGrabber.update();
	// get CV color image from vidGrabber
	colorImg.setFromPixels(vidGrabber.getPixelsRef());
	// grayscale color image
	current = colorImg;
	// get absolute difference
	// (change between previous and current will be white, unchanged will be black
	difference.absDiff(current, previous);
	// thresholding image increases contrast
	difference.threshold(30);
    difference.mirror(false, true);
    difference.flagImageChanged();

	for (int i = 0; i < bubbles.size(); ++i) {
        int movementAmt = 0;
        pixels = difference.getPixels();
        float leftX = bubbles[i].position.x - (bubbles[i].radius / 2);
        float topY = bubbles[i].position.y - (bubbles[i].radius / 2);
        float rightX = bubbles[i].position.x + (bubbles[i].radius / 2);
        float bottomY = bubbles[i].position.y + (bubbles[i].radius / 2);
		// search the bounds of each bubble
        for (int y = topY; y < bottomY; y++) {
            for (int x = leftX; x < rightX; x++) {
				// if the lightness of the pixel is greater than 150 (not black)
				/* NOTE: originally was pixels.getColor(x, y) but immediately throws an
				 access violation on my computer. Changing it to (y, x) helps temporarily */
                if(pixels.getColor(y, x).getLightness() > 150) {
                    movementAmt++;
                }
            }
        }
		// we want to make sure there was a substantial amount of movement by the bubble
		if (movementAmt > 10) {
			// "pop" the bubble
			bubbles.erase((bubbles.begin() + i));
			
			#ifdef USE_TWO_SOUNDS
			// outcome of randNum determines the popping sound that is played
			int randNum = (int)ofRandom(0, 2);
			if (randNum == 0) { bubblePop1.play(); }
			else if (randNum == 1) { bubblePop2.play(); }
			#else
			bubblePop2.play();
			#endif

			--i; //make sure you don't skip over a bubble
		} else {
			// bubble did not get popped, increment its position
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
	// draw video to screen
	forDrawing.setFromPixels(vidGrabber.getPixelsRef());
	forDrawing.mirror(false, true);
	forDrawing.draw(0, 0);
	
	int frameNum = ofGetFrameNum();
	// draw a new bubble approximately every second
	if (frameNum % 30 == 0) {
		Bubble bubble;
		ofDrawCircle(bubble.position.x, bubble.position.y, bubble.radius);
		ofSetColor(bubble.color);
		ofSetLineWidth(5);
		ofNoFill();
		//add bubble to bubbles vector
		bubbles.push_back(bubble);
	}
	// this makes sure the bubbles that already exist are still being drawn
	if (updated == true) {
		for (int i = 0; i < bubbles.size(); ++i) {
			ofDrawCircle(bubbles[i].position.x, bubbles[i].position.y, bubbles[i].radius);
		}
	}
}


// Spacebar clears the bubbles
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		bubbles.clear();
	}
}
