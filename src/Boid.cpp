#include "Boid.h"
#include "ofApp.h"

Boid::Boid()
{
    pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
    vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
    acceleration.set(0, 0);
    radius = ofRandom(6, 9);
    maxspeed = ofRandom(0.12, 0.23);

    color.set(125);
    stroke = 255;

    isAlive = true;
    searchDist = 40;
}

void Boid::update(vector<Boid*> boids)
{

    updatePhysics();
    boundaryPhysics();
    behaviours(boids);
    getColor();
}

void Boid::updatePhysics()
{
    vel += acceleration;
    vel.limit(maxspeed);
    pos += vel;
    acceleration *= 0;
}

void Boid::boundaryPhysics()
{
    if (pos.x < 0) {
        pos.x = ofGetWidth();
        //vel.x *= -1;
    }
    else if (pos.x > ofGetWidth()) {
        pos.x = 0;
        //vel.x *= -1;
    }

    if (pos.y < 0) {
        pos.y = ofGetHeight();
        //vel.y *= -1;
    }
    else if (pos.y > ofGetHeight()) {
        pos.y = 0;
        //vel.y *= -1;
    }
}

void Boid::applyForce(ofVec2f force)
{
    acceleration += force;
}

void Boid::behaviours(vector<Boid*> boids)
{
    ofVec2f coh = cohesion(boids);
    ofVec2f aln = align(boids);
    ofVec2f sep = separate(boids);

    coh *= 0.05;
    aln *= 0.05;
    sep *= 3.0;

    applyForce(coh);
    applyForce(aln);
    applyForce(sep);
}

ofVec2f Boid::seekTarget(ofVec2f target)
{
    ofVec2f desired = target - pos;
    desired.normalize();
    desired *= maxspeed;
    ofVec2f steer = desired - vel;
    steer.limit(maxforce);
    return steer;
}

ofVec2f Boid::cohesion(vector<Boid*> boids)
{
    float neighbourdist = 50;
    ofVec2f sum;
    sum.set(0, 0);
    int count = 0;

    for (int i = 0; i < BOIDCOUNT; i++) {
        float d = pos.distance(boids[i]->pos);

        if ((d > 0) && (d < neighbourdist)) {
            sum += boids[i]->pos;
            count++;
        }
    }
    if (count > 0) {
        sum /= count;
        return seekTarget(sum);
    }
    else {
        ofVec2f vec;
        vec.set(0, 0);
        return vec;
    }
}

ofVec2f Boid::align(vector<Boid*> boids)
{
    float neighbourdist = 50;
    ofVec2f sum;
    sum.set(0, 0);
    int count = 0;

    for (int i = 0; i < BOIDCOUNT; i++) {
        float d = pos.distance(boids[i]->pos);

        if ((d > 0) && (d < neighbourdist)) {
            sum += boids[i]->vel;
            count++;
        }
    }
    if (count > 0) {
        sum /= count;
        sum.normalize();
        sum *= maxspeed;
        ofVec2f steer = sum - vel;
        steer.limit(maxforce);
        return steer;
    }
    else {
        ofVec2f vec;
        vec.set(0, 0);
        return vec;
    }
}

ofVec2f Boid::separate(vector<Boid*> boids)
{
    ofVec2f steer;
    steer.set(0, 0);
    int count = 0;

    for (int i = 0; i < BOIDCOUNT; i++) {
        float desiredSeparation = (radius * 2) + 1;
        float d = pos.distance(boids[i]->pos);

        if ((d > 0) && (d < desiredSeparation)) {
            ofVec2f diff = pos - boids[i]->pos;
            diff.normalize();
            diff /= d;
            steer += diff;
            count++;
        }
    }
    if (count > 0) {
        steer /= count;
    }
    if (steer.length() > 0) {
        steer.normalize();
        steer *= maxspeed;
        steer -= vel;
        steer.limit(maxforce);
    }
    return steer;
}

ofVec2f Boid::seekFood()
{
    return ofVec2f();
}

ofVec2f Boid::avoidThreat()
{
    return ofVec2f();
}

void Boid::eatFood()
{
}

void Boid::mitosis()
{
}

void Boid::getColor()
{
    int d = ofDist(pos.x, pos.y, ofGetWidth() / 2, ofGetHeight() / 2);
    color = ofColor(ofMap(d, ofGetWidth() / 2, 0, 25, 100));
}

void Boid::draw()
{  
    ofFill();
    ofSetColor(color);
    ofDrawCircle(pos.x, pos.y, radius);

    ofNoFill();
    ofSetColor(stroke);
    ofSetLineWidth(0.5);
    ofDrawCircle(pos.x, pos.y, radius);
}