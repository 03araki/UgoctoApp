#include "ofApp.h"
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
	// monitor setting
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetFullscreen(true);
	ofBackground(0, 0, 0);

	// Box2D initial setting
	box2d.init();
	iGravityAngle = 0;
	box2d.setGravity(5 * sin(2 * PI*iGravityAngle / 360.0), 5 * cos(2 * PI*iGravityAngle / 360.0));
	box2d.createBounds(0, 0, ofGetWidth(), ofGetHeight());
	box2d.setFPS(30);

	// load sound data
	sound1.loadSound("water-drop3.mp3");
	sound2.loadSound("katana-gesture2.mp3");
	sound3.loadSound("washing-machine-operation1.mp3");
	sound3.setLoop(true);
	sound3.play();
	sound3.setPaused(true);

	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);

	bThread = true;
	if (!thread.start(4)) {
		printf("Sensor Init failed.\n");
		bThread = false;
	}

	bSWStatus = false;
	bAccStatus = false;
	bEncRotate = false;
	iPrevEncCount = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	// Check Sensor output
	// Switch
	if (thread.bSwitch && !bSWStatus) {
		bSWStatus = true;
		float r = ofRandom(40, 60);
		auto circle = std::make_shared<ofxBox2dCircle>();
		circle.get()->setPhysics(1.0, 0.8, 0.5);
		circle.get()->setup(box2d.getWorld(), ofRandom(r, ofGetWidth() - r), ofRandom(r, ofGetHeight() - r), r);
		circles.push_back(circle);
		int color = (int)floor(ofRandom(0, 6.9));
		circle_colors.push_back(color);
		sound1.play();
	}
	if (!thread.bSwitch && bSWStatus) bSWStatus = false;
	
	// Encorder
	iGravityAngle = (int)ceil(thread.iEncCount / 4.0);
	box2d.setGravity(5 * sin(2 * PI*iGravityAngle / 360.0), 5 * cos(2 * PI*iGravityAngle / 360.0));
	// if rotate the handle, play the rotation sound
	if (abs(thread.iEncCount - iPrevEncCount) > 2) bEncRotate = true;
	else bEncRotate = false;
	iPrevEncCount = thread.iEncCount;
	sound3.setPaused(!bEncRotate);
	
	// Acc Sensor
	if (thread.iYAcc > 150 && !bAccStatus) {
		bAccStatus = true;
		if (circles.size() > 0) {
			int erase_num = (int)floor(ofRandom(0, circles.size() - 0.1));
			circles.erase(circles.begin() + erase_num);
			circle_colors.erase(circle_colors.begin() + erase_num);
		}
		sound2.play();
	}
	if (thread.iYAcc < 150 && bAccStatus) bAccStatus = false;

	box2d.update();

	fbo.begin();
	ofClear(0);
	ofSetColor(255, 40, 0);
	ofTranslate(ofGetWidth() / 2.0, ofGetHeight() / 2.0);
	ofRotate(-iGravityAngle);
	ofFill();
	ofDrawRectangle(-20, -100, 40, 200);
	ofTriangle(0, 150, -50, 50, 50, 50);
	ofRotate(iGravityAngle);
	ofTranslate(-ofGetWidth() / 2.0, -ofGetHeight() / 2.0);
	for (int i = 0; i < circles.size(); i++) {
		ofFill();
		switch (circle_colors[i]) {
		case 0:
			ofSetColor(255, 209, 209); break;
		case 1:
			ofSetColor(255, 255, 153); break;
		case 2:
			ofSetColor(203, 242, 102); break;
		case 3:
			ofSetColor(180, 235, 250); break;
		case 4:
			ofSetColor(237, 197, 143); break;
		case 5:
			ofSetColor(135, 231, 176); break;
		case 6:
			ofSetColor(199, 178, 222); break;
		}
		circles[i]->draw();

	}
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void ofApp::exit()
{
	thread.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	/*
	switch (key) {
	case OF_KEY_RIGHT:
		iGravityAngle = (iGravityAngle + 1) % 360;
		box2d.setGravity(2 * sin(2 * PI*iGravityAngle / 360.0), 2 * cos(2 * PI*iGravityAngle / 360.0));
		break;
	case OF_KEY_LEFT:
		if (iGravityAngle == 0) iGravityAngle = 360;
		iGravityAngle = (iGravityAngle - 1) % 360;
		box2d.setGravity(2 * sin(2 * PI*iGravityAngle / 360.0), 2 * cos(2 * PI*iGravityAngle / 360.0));
		break;
	case 'r':
		bEncRotate = !bEncRotate;
		sound3.setPaused(!bEncRotate);
		break;
	case 'd':
		if (circles.size() > 0) {
			int erase_num = (int)floor(ofRandom(0, circles.size() - 0.1));
			circles.erase(circles.begin() + erase_num);
			circle_colors.erase(circle_colors.begin() + erase_num);
		}
		sound2.play();
		break;
	case 'a':
		float r = ofRandom(30, 50);
		auto circle = std::make_shared<ofxBox2dCircle>();
		circle.get()->setPhysics(1.0, 0.8, 0.5);
		circle.get()->setup(box2d.getWorld(), ofRandom(r, ofGetWidth() - r), ofRandom(r, ofGetHeight() - r), r);
		circles.push_back(circle);
		int color = (int)floor(ofRandom(0, 6.9));
		circle_colors.push_back(color);
		sound1.play();
		break;
	}
	*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
