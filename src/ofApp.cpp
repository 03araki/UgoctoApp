#include "ofApp.h"
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
	// monitor setting
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);

	// Box2D initial setting
	box2d.init();
	iGravityAngle = 0;
	box2d.setGravity(2 * sin(2 * PI*iGravityAngle / 360.0), 2 * cos(2 * PI*iGravityAngle / 360.0));
	box2d.createBounds(0, 0, ofGetWidth(), ofGetHeight());
	box2d.setFPS(30);

}

//--------------------------------------------------------------
void ofApp::update(){
	box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 0, 0);
	ofTranslate(ofGetWidth() / 2.0, ofGetHeight() / 2.0);
	ofRotate(-iGravityAngle);
	ofDrawLine(0, 0, 0, 100);
	ofRotate(iGravityAngle);
	ofTranslate(-ofGetWidth() / 2.0, -ofGetHeight() / 2.0);
	for (int i = 0; i < circles.size(); i++) {
		ofFill();
		ofSetColor(0, 127, 255);
		circles[i]->draw();
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
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
	case 'd':
		if(circles.size() > 0) 
			circles.erase(circles.begin() + (int)ofRandom(0, circles.size() - 1));
		break;
	case 'a':
		float r = ofRandom(20, 30);
		auto circle = std::make_shared<ofxBox2dCircle>();
		circle.get()->setPhysics(1.0, 0.8, 0.5);
		circle.get()->setup(box2d.getWorld(), ofRandom(r, ofGetWidth() - r), ofRandom(r, ofGetHeight() - r), r);
		circles.push_back(circle);
		break;
	}
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
