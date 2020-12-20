#include "Food.h"

Food::Food()
{
	pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
	radius = 2.5;
	color.set(255, 255, 0);
    stroke = 255;
}

void Food::update()
{
    getColor();
}

void Food::getColor()
{
    int d = ofDist(pos.x, pos.y, ofGetWidth()/2, ofGetHeight()/2);
    color = ofColor(255, 255, 0, ofMap(d, ofGetWidth()/2, 0, 25, 100));
}

void Food::draw()
{
    ofFill();
    ofSetColor(color);
    ofDrawCircle(pos.x, pos.y, radius);

    ofNoFill();
    ofSetColor(ofColor(stroke, stroke, 0));
    ofSetLineWidth(0.2);
    ofDrawCircle(pos.x, pos.y, radius);
}