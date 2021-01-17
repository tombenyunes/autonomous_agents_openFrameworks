#pragma once

#include "ofMain.h"
#include "Food.h"

class Boid {

public:
    Boid::Boid(ofVec2f _pos = { -1, -1 }, float _radius = -1);

    void update(vector<Boid*>* boids, vector<Food*>* foods);
    void updatePhysics();
    void boundaryPhysics();
    void applyForce(ofVec2f force);
    void behaviours(vector<Boid*>* boids, vector<Food*>* foods);
    ofVec2f seekTarget(ofVec2f target);
    ofVec2f cohesion(vector<Boid*>* boids);
    ofVec2f align(vector<Boid*>* boids);
    ofVec2f separate(vector<Boid*>* boids);
    ofVec2f seekFood(vector<Boid*>* boids, vector<Food*>* foods);
    ofVec2f avoidThreat();
    void eatFood(vector<Food*>* foods);
    void mitosis(vector<Boid*>* boids);
    void getColor();
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

    vector<ofVec2f> nearestFoods;
};