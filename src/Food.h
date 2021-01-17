#pragma once

#include "ofMain.h"

class Food {

public:
	Food();
	~Food();
	
	void update();
	void randomWalk();
	void getColor();
	void draw();

	ofVec2f pos;
	float speed;
	ofVec2f dir;
	int radius;
	ofColor color;
	int stroke;
	bool isAlive;
	bool absorbing;
};