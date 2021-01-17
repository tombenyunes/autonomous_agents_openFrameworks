#include "Food.h"

Food::Food()
{
	pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
    speed = 0.075;
    dir = { ofRandom(-0.075, 0.075), ofRandom(-0.075, 0.075) };
	radius = 2.5;
	color.set(255, 255, 0);
    stroke = 255;
    isAlive = true;
    absorbing = false;
}

Food::~Food()
{

}

void Food::update()
{
    randomWalk();
    getColor();
}

void Food::randomWalk()
{
    int r = round(ofRandom(0, 100));

    if (r < 2) {
        dir = { ofRandom(-0.075, 0.075), ofRandom(-0.075, 0.075) };
    }

    if (!absorbing) {
        dir.scale(0.075);
    }
    else {
        dir.scale(5);
    }

    pos += dir;
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