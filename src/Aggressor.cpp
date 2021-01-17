#include "Aggressor.h"

Aggressor::Aggressor(ofVec2f _pos, float _radius)
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
        radius = 12;
    }
    else {
        radius = _radius;
    }

    maxspeed = 0.28;

    color.set(0);
    stroke = 255;

    isAlive = true;
    searchDist = radius + 125;
    pullRange = radius + 100;
    chasing = false;
}

void Aggressor::update(vector<Boid*>* boids, vector<Food*>* foods)
{
    updatePhysics();
    boundaryPhysics();
    behaviours(boids, foods);

    absorbCells(boids, foods);
}

void Aggressor::updatePhysics()
{
    vel += acceleration;
    vel.limit(maxspeed);
    pos += vel;
    acceleration *= 0;
}

void Aggressor::boundaryPhysics()
{
    if (pos.x < 0) {
        vel.x *= -1;
    }
    else if (pos.x > ofGetWidth()) {
        vel.x *= -1;
    }

    if (pos.y < 0) {
        vel.y *= -1;
    }
    else if (pos.y > ofGetHeight()) {
        vel.y *= -1;
    }
}

void Aggressor::applyForce(ofVec2f force)
{
    acceleration += force;
}

void Aggressor::behaviours(vector<Boid*>* boids, vector<Food*>* foods)
{
    ofVec2f sf = seekFood(boids, foods);
    ofVec2f pc = preferCenter();

    sf *= 1.0;
    if (chasing) {
        pc *= 0;
    }
    else {
        pc *= 1.0;
    }

    applyForce(sf);
    applyForce(pc);
}

ofVec2f Aggressor::seekTarget(ofVec2f target)
{
    ofVec2f desired = target - pos;
    desired.normalize();
    desired *= maxspeed;
    ofVec2f steer = desired - vel;
    steer.limit(maxforce);
    return steer;
}

ofVec2f Aggressor::seekFood(vector<Boid*>* boids, vector<Food*>* foods)
{
    vector<float> dists;
    vector<ofVec2f> sum;
    int count{};
    chasing = false;
    int minIndex;
    nearestFoods.clear();

    for (int i = 0; i < boids->size(); i++) {
        float d = pos.distance((*boids)[i]->pos);

        if (d <= searchDist) {
            nearestFoods.push_back({ (*boids)[i]->pos.x, (*boids)[i]->pos.y });
            chasing = true;

            sum.push_back((*boids)[i]->pos);
            count++;
        }
    }
    if (count > 0) {
        for (int i = 0; i < sum.size(); i++) {
            float d = pos.distance(sum[i]);

            dists.push_back(d);

            vector<float>::iterator result = min_element(dists.begin(), dists.end());
            minIndex = distance(dists.begin(), result);
        }

        return seekTarget(sum[minIndex]);
    }
    else {
        return ofVec2f{ 0, 0 };
    }
}

ofVec2f Aggressor::preferCenter()
{
    float d = pos.distance( { (float)ofGetWidth() / 2, (float)ofGetHeight() / 2 } );

    ofVec2f thisVec = { pos.x, pos.y };
    ofVec2f centerVec = { (float)ofGetWidth()/2, (float)ofGetHeight()/2 };
    ofVec2f vec = centerVec - thisVec;

    if (d > 250) {
        return vec;
    }
    else {
        return ofVec2f{ 0, 0 };
    }
}

void Aggressor::absorbCells(vector<Boid*>* boids, vector<Food*>* foods)
{
    for (int i = 0; i < boids->size(); i++) {
        float d = pos.distance((*boids)[i]->pos);

        if (d <= pullRange) {
            ofVec2f thisPos = { pos };
            ofVec2f otherPos = { (*boids)[i]->pos };
            ofVec2f vec = otherPos - thisPos;

            (*boids)[i]->vel = vec;
            (*boids)[i]->maxspeed -= 0.1;
        }

        if (d < (radius + (*boids)[i]->radius)) {
            (*boids)[i]->isAlive = false;

            float sum1 = PI * radius * radius + PI * ((*boids)[i]->radius * 1) * ((*boids)[i]->radius * 1);
            float sum2 = (sqrt(sum1 / PI));
            radius = sum2;
        }
    }

    for (int i = 0; i < foods->size(); i++) {
        float d = pos.distance((*foods)[i]->pos);

        if (d <= pullRange) {
            ofVec2f thisPos = { pos };
            ofVec2f otherPos = { (*foods)[i]->pos };
            ofVec2f vec = otherPos - thisPos;

            (*foods)[i]->absorbing = true;
            (*foods)[i]->dir = -vec;
            (*foods)[i]->speed--;
        }

        if (d < (radius + (*foods)[i]->radius)) {
            (*foods)[i]->isAlive = false;

            float sum1 = PI * radius * radius + PI * ((*foods)[i]->radius * 1) * ((*foods)[i]->radius * 1);
            float sum2 = (sqrt(sum1 / PI));
            radius = sum2;
        }
    }
}

void Aggressor::draw()
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
}
