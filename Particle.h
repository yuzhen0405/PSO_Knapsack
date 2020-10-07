#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

#define DIMENSION 10

class Particle {
public:
    Particle();

    int getPBestFitness();

    void setPBestFitness(int pBest);

    int *getPBestLocation();

    void setPBestLocation(int index, int location);

    int getFitness();

    void setFitness(int fitness);

    int *getVelocity();

    void setVelocity(int index, int velocity);

    int *getLastVelocity();

    void setLastVelocity(int index, int lastVelocity);

    int *getLocation();

    void setLocation(int index, int location);

private:
    int fitness;
    int velocity[DIMENSION];
    int lastVelocity[DIMENSION];
    int location[DIMENSION];
    int pBestFitness;
    int pBestLocation[DIMENSION];
};

#endif //PSO_PARTICLE_H
