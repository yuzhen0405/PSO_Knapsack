#include "Particle.h"

Particle::Particle() {
    setFitness(0);
    setPBestFitness(0);
    for (int i = 0; i < DIMENSION; i++) {
        setVelocity(i, 0);
        setLastVelocity(i, 0);
        setLocation(i, 0);
        setPBestLocation(i, 0);
    }
}

int *Particle::getVelocity() {
    return this->velocity;
}

void Particle::setVelocity(int i, int v) {
    this->velocity[i] = v;
}

int *Particle::getLastVelocity() {
    return this->lastVelocity;
}

void Particle::setLastVelocity(int i, int lv) {
    this->lastVelocity[i] = lv;
}

int *Particle::getLocation() {
    return this->location;
}

void Particle::setLocation(int i, int l) {
    this->location[i] = l;
}

int Particle::getPBestFitness() {
    return this->pBestFitness;
}

void Particle::setPBestFitness(int p) {
    this->pBestFitness = p;
}

int *Particle::getPBestLocation() {
    return this->pBestLocation;
}

void Particle::setPBestLocation(int i, int l) {
    this->pBestLocation[i] = l;
}

int Particle::getFitness() {
    return this->fitness;
}

void Particle::setFitness(int f) {
    this->fitness = f;
}
