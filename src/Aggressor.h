#pragma once

#include "ofMain.h"
#include "Food.h"
#include "Boid.h"

class Aggressor {

public:
    Aggressor::Aggressor(ofVec2f _pos = { -1, -1 }, float _radius = -1);

    void update(vector<Boid*>* boids, vector<Food*>* foods);
    void updatePhysics();
    void boundaryPhysics();
    void applyForce(ofVec2f force);
    void behaviours(vector<Boid*>* boids, vector<Food*>* foods);
    ofVec2f seekTarget(ofVec2f target);
    ofVec2f seekFood(vector<Boid*>* boids, vector<Food*>* foods);
    ofVec2f preferCenter();
    void absorbCells(vector<Boid*>* boids, vector<Food*>* foods);
    void draw();

    ofVec2f pos;
    float radius;
    float maxspeed;
    float maxforce = 0.05;
    ofVec2f acceleration;
    ofVec2f vel;

    ofColor color;
    int stroke;

    bool isAlive;
    int searchDist;
    int pullRange;
    bool chasing;

    vector<ofVec2f> nearestFoods;
};