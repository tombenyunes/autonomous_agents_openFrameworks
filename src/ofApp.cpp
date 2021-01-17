#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(1);
	ofEnableAntiAliasing();

	for (int i = 0; i < FOODCOUNT; i++) {
		Food* f = new Food{};
		myFoods.push_back(f);
	}

	for (int i = 0; i < BOIDCOUNT; i++) {
		Boid* b = new Boid{};
		myBoids.push_back(b);
	}

	for (int i = 0; i < AGGRESSORCOUNT; i++) {
		Aggressor* a = new Aggressor{};
		myAggressors.push_back(a);
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	ofBackground(0);

	for (int i = 0; i < myFoods.size(); i++) {
		myFoods[i]->update();

		if (!myFoods[i]->isAlive) {
			myFoods.erase(myFoods.begin() + i);
			Food* f = new Food{};
			myFoods.push_back(f);
		}
	}
	
	for (int i = 0; i < myBoids.size(); i++) {
		myBoids[i]->update(&myBoids, &myFoods);

		if (!myBoids[i]->isAlive) {
			myBoids.erase(myBoids.begin() + i);
		}
	}

	for (int i = 0; i < myAggressors.size(); i++) {
		myAggressors[i]->update(&myBoids, &myFoods);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	for (int i = 0; i < myFoods.size(); i++) {
		myFoods[i]->draw();
	}
	for (int i = 0; i < myBoids.size(); i++) {
		myBoids[i]->draw();
	}
	for (int i = 0; i < myAggressors.size(); i++) {
		myAggressors[i]->draw();
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
