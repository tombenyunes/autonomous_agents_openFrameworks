#include "Boid.h"
#include "ofApp.h"

Boid::Boid(ofVec2f _pos, float _radius)
{
    if (_pos.x == -1 || _pos.y == -1) {
        pos.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
    }
    else {
        pos.set(_pos);
    }

    vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
    acceleration.set(0, 0);
    
    if (_radius == -1) {
        radius = ofRandom(6, 9);
    }
    else {
        radius = _radius;
    }

    maxspeed = ofRandom(0.12, 0.23);

    color.set(125);
    stroke = 255;

    isAlive = true;
    searchDist = 40;
}

void Boid::update(vector<Boid*>* boids, vector<Food*>* foods)
{
    updatePhysics();
    boundaryPhysics();
    behaviours(boids, foods);
    getColor();

    eatFood(foods);
    mitosis(boids);
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

void Boid::behaviours(vector<Boid*>* boids, vector<Food*>* foods)
{
    ofVec2f coh = cohesion(boids);
    ofVec2f aln = align(boids);
    ofVec2f sep = separate(boids);
    ofVec2f sf = seekFood(boids, foods);

    coh *= 0.05;
    aln *= 0.05;
    sep *= 3.0;
    sf *= 1.0;

    applyForce(coh);
    applyForce(aln);
    applyForce(sep);
    applyForce(sf);
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

ofVec2f Boid::cohesion(vector<Boid*>* boids)
{
    float neighbourdist = 50;
    ofVec2f sum {};
    int count = 0;

    for (int i = 0; i < (*boids).size(); i++) {
        float d = pos.distance((*boids)[i]->pos);

        if ((d > 0) && (d < neighbourdist)) {
            sum += (*boids)[i]->pos;
            count++;
        }
    }
    if (count > 0) {
        sum /= count;
        return seekTarget(sum);
    }
    else {
        ofVec2f vec {};
        return vec;
    }
}

ofVec2f Boid::align(vector<Boid*>* boids)
{
    float neighbourdist = 50;
    ofVec2f sum {};
    int count = 0;

    for (int i = 0; i < (*boids).size(); i++) {
        float d = pos.distance((*boids)[i]->pos);

        if ((d > 0) && (d < neighbourdist)) {
            sum += (*boids)[i]->vel;
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
        ofVec2f vec {};
        return vec;
    }
}

ofVec2f Boid::separate(vector<Boid*>* boids)
{
    ofVec2f steer {};
    int count = 0;

    for (int i = 0; i < (*boids).size(); i++) {
        float desiredSeparation = (radius * 2) + 1;
        float d = pos.distance((*boids)[i]->pos);

        if ((d > 0) && (d < desiredSeparation)) {
            ofVec2f diff = pos - (*boids)[i]->pos;
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

ofVec2f Boid::seekFood(vector<Boid*>* boids, vector<Food*>* foods)
{
    ofVec2f sum {};
    vector<float> dists;
    vector<ofVec2f> sum2;
    int count {};
    vector<float>::iterator closestFood;
    int minIndex;
    nearestFoods.clear();

    for (int i = 0; i < foods->size(); i++) {
        int d = ofDist(pos.x, pos.y, (*foods)[i]->pos.x, (*foods)[i]->pos.y);
        
        if (d <= (radius + searchDist)) {
            nearestFoods.push_back({ (*foods)[i]->pos.x, (*foods)[i]->pos.y });
            sum2.push_back((*foods)[i]->pos);
            count++;
        }
    }
    if (count > 0) {
        for (int i = 0; i < sum2.size(); i++) {
            float d = pos.distance(sum2[i]);
            dists.push_back(d);

            vector<float>::iterator result = min_element(dists.begin(), dists.end());
            minIndex = distance(dists.begin(), result);
        }
        return seekTarget(sum2[minIndex]);
    }
    else {
        ofVec3f vec {};
        return vec;
    }

    return ofVec2f();
}

ofVec2f Boid::avoidThreat()
{
    return ofVec2f();
}

void Boid::eatFood(vector<Food*>* foods)
{
    if (foods->size() > 0) {
        for (int i = 0; i < foods->size(); i++) {
            int d = ofDist(pos.x, pos.y, (*foods)[i]->pos.x, (*foods)[i]->pos.y);

            if ((d < (radius + (*foods)[i]->radius)) || (d <= 0)) {
                if (radius < 15) {
                    radius++;
                    (*foods)[i]->isAlive = false;
                }
            }
        }
    }
}

void Boid::mitosis(vector<Boid*>* boids)
{
    int radius_int = round(radius);

    if ( (radius_int % 10 == 0) /*&& (boids.size() <= 150)*/ ) {
        radius /= 2;
        Boid* b = new Boid{ {pos.x, pos.y}, radius };
        boids->push_back(b);
    }
}

void Boid::getColor()
{
    int d = ofDist(pos.x, pos.y, ofGetWidth() / 2, ofGetHeight() / 2);
    color = ofColor(ofMap(d, ofGetWidth() / 2, 0, 25, 100));
}

void Boid::draw()
{
    if (nearestFoods.size() > 0) {
        for (int i = 0; i < nearestFoods.size(); i++) {
            ofSetLineWidth(1);
            ofSetColor(125, 125, 125);  // develop this
            ofLine(ofVec3f(pos.x, pos.y), ofVec3f(nearestFoods[i].x, nearestFoods[i].y));
        }
    }

    ofFill();
    ofSetColor(color);
    ofDrawCircle(pos.x, pos.y, radius);

    ofNoFill();
    ofSetColor(stroke);
    ofSetLineWidth(0.5);
    ofDrawCircle(pos.x, pos.y, radius);

    //int radius_int = round(radius);
    //ofDrawBitmapString(radius_int, pos.x-4, pos.y+4);
}