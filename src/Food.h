#pragma once

#include "ofMain.h"

class Food {

public:
	Food();
	
	void update();
	void getColor();
	void draw();

	ofVec2f pos;
	int radius;
	ofColor color;
	int stroke;
};