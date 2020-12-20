#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(1);
	ofEnableAntiAliasing();

	for (int i = 0; i < BOIDCOUNT; i++) {
		Food* f = new Food{};
		myFoods.push_back(f);
		Boid* b = new Boid{};
		myBoids.push_back(b);
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	ofBackground(0);

	//if (ofGetFrameNum() % 2 == 0) {
	for (int i = 0; i < BOIDCOUNT; i++) {
		myFoods[i]->update();
		myBoids[i]->update(myBoids);
	}
	//}
}

//--------------------------------------------------------------
void ofApp::draw()
{

	for (int i = 0; i < BOIDCOUNT; i++) {
		myFoods[i]->draw();
		myBoids[i]->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
