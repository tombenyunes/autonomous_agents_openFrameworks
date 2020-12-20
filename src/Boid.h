#pragma once

#include "ofMain.h"

class Boid {

public:
    Boid();

    void update(vector<Boid*> boids);
    void updatePhysics();
    void boundaryPhysics();
    void applyForce(ofVec2f force);
    void behaviours(vector<Boid*> boids);
    ofVec2f seekTarget(ofVec2f sum);
    ofVec2f cohesion(vector<Boid*> boids);
    ofVec2f align(vector<Boid*> boids);
    ofVec2f separate(vector<Boid*> boids);
    ofVec2f seekFood();
    ofVec2f avoidThreat();
    void eatFood();
    void mitosis();
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
};