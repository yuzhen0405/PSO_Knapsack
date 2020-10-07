#ifndef PSO_PSO_H
#define PSO_PSO_H

#include "Particle.h"
#include <fstream>

#define POPULATION 20
#define ROUND 2000
#define KNAPSACK_SIZE 275

#define W 1.0
#define C1 1.0
#define C2 1.0

#define DEBUG_MODE 0
#define PRINT_ROUND_RESULT 0
#define CALC_FITNESS_MODE 1
#define EPIN_OUTPUT 0 // NOTE: integer encoding cannot use this function...

const char name[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
const int weight[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const int value[10] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

class PSO {
private:
    Particle particle[POPULATION];
    Particle gBest;
    std::ofstream fileOut;

    void calcFitness();

    void update();

    void move();

public:
    PSO();

    ~PSO();

    void run();

    void prtResult();

    Particle getGBest();

    void fileOpen();

    void outputEPIN(int round);

    void fileClose();
};

#endif //PSO_PSO_H
