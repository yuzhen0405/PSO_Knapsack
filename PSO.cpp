#include "PSO.h"
#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

int myRandom(int start, int end);

PSO::PSO() {
#if EPIN_OUTPUT
    fileOpen();
#endif
    // Initialize
    this->gBest.setFitness(0);
    this->gBest.setPBestFitness(0);

    for (int i = 0; i < DIMENSION; i++) {
        this->gBest.setLocation(i, 0);
        this->gBest.setVelocity(i, 0);
        this->gBest.setLastVelocity(i, 0);
        this->gBest.setPBestLocation(i, 0);
    }

    for (int i = 0; i < POPULATION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            particle[i].setVelocity(j, myRandom(-10, 10));
            particle[i].setLastVelocity(j, myRandom(-10, 10));
            particle[i].setLocation(j, myRandom(0, 10));
        }
    }
}

PSO::~PSO() {
//    cout << "End of pso" << endl;
#if EPIN_OUTPUT
    fileClose();
#endif
}

void PSO::run() {
    for (int i = 0; i < ROUND; i++) {
        calcFitness();
        update();
        move();
#if EPIN_OUTPUT
        outputEPIN(i);
#endif
    }
}

void processOW(Particle *p) {
    // drop an item which is the lowest cost-performance ratio one
    int w = 0, v = 0;

    for (int i = 0; i < DIMENSION; i++) {
        w += p->getLocation()[i] * weight[i];
        v += p->getLocation()[i] * value[i];
    }

    for (int i = DIMENSION - 1; i >= 0; i--) {
        int tmp = p->getLocation()[i];
        if (tmp > 0) {
            tmp--;
            p->setLocation(i, tmp);
            w -= weight[i];
            v -= value[i];

            if (w <= KNAPSACK_SIZE) {
                p->setFitness(v);
                break;
            }
        }
    }
}

void PSO::calcFitness() {
    for (int i = 0; i < POPULATION; i++) {
        int w = 0, v = 0;

        for (int j = 0; j < DIMENSION; j++) {
            w += particle[i].getLocation()[j] * weight[j];
            v += particle[i].getLocation()[j] * value[j];
        }

        if (w > KNAPSACK_SIZE) {
#if CALC_FITNESS_MODE
            // drop a lowest C/P value item
            processOW(&particle[i]);
#else
            // punishment coefficient
            particle[i].setFitness(v * (0.9 - ((w - KNAPSACK_SIZE) / (double) (2 * KNAPSACK_SIZE))));
#endif
        } else {
            particle[i].setFitness(v);
        }

#if DEBUG_MODE
        cout << "weight: " << w << endl;
        cout << "value: " << v << endl;
        cout << "fitness: " << particle[i].getFitness() << endl;
#endif

        // Check if it need to update pBest
        if (particle[i].getFitness() > particle[i].getPBestFitness()) {
            particle[i].setPBestFitness(particle[i].getFitness());
            for (int j = 0; j < DIMENSION; j++) {
                particle[i].setPBestLocation(j, particle[i].getLocation()[j]);
            }
            // Check if need to update gBest
            if (particle[i].getPBestFitness() > this->gBest.getFitness()) {
                this->gBest.setFitness(particle[i].getPBestFitness());
                this->gBest.setPBestFitness(particle[i].getPBestFitness());
                for (int j = 0; j < DIMENSION; j++) {
                    this->gBest.setLocation(j, particle[i].getLocation()[j]);
                    this->gBest.setPBestLocation(j, particle[i].getPBestLocation()[j]);
                    this->gBest.setVelocity(j, particle[i].getVelocity()[j]);
                    this->gBest.setLastVelocity(j, particle[i].getLastVelocity()[j]);
                }
            }
        }
    }
}

void PSO::update() {
    for (int i = 0; i < POPULATION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            particle[i].setVelocity(j,
                                    W * particle[i].getLastVelocity()[j] +
                                    C1 * (myRandom(0, 10) / 10.0) *
                                    (particle[i].getPBestLocation()[j] - particle[i].getLocation()[j]) +
                                    C2 * (myRandom(0, 10) / 10.0) *
                                    (this->gBest.getLocation()[j] - particle[i].getLocation()[j]));
        }
    }
}

void PSO::move() {
    for (int i = 0; i < POPULATION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            // update location and velocity of next round
            particle[i].setLastVelocity(j, particle[i].getVelocity()[j]);
            particle[i].setLocation(j, particle[i].getLocation()[j] + particle[i].getVelocity()[j]);

            // stop it while it got out of bound
            if (particle[i].getLocation()[j] > 10) {
                particle[i].setLocation(j, 10);
            } else if (particle[i].getLocation()[j] < 0) {
                particle[i].setLocation(j, 0);
            }
        }
    }
}

void PSO::prtResult() {
    cout << "gBest fitness: " << this->gBest.getFitness() << endl;
    cout << "Location: ";
    for (int i = 0; i < DIMENSION; i++) {
        cout << this->gBest.getLocation()[i] << ' ';
    }
    cout << endl;
}

Particle PSO::getGBest() {
    return this->gBest;
}

void PSO::fileOpen() {
    fileOut.open("../output/PSO_result.epin", ios::out);
    fileOut << "Particle : " << endl;
}

void PSO::outputEPIN(int round) {
    fileOut << '*' << (round + 1) << ' ';
    fileOut << this->gBest.getFitness() << ": ";
    for (int i = 0; i < POPULATION; i++) {
        fileOut << this->particle[i].getFitness() << ' ';
        fileOut << "Bag" << (i + 1) << ' ';
        for (int j = 0; j < DIMENSION; j++) {
            fileOut << this->particle[i].getLocation()[j] << ',';
            fileOut << fixed << setprecision(1) << 0 << ',';
            fileOut << "bit" << (j + 1);
            if (j == DIMENSION - 1)
                fileOut << '/';
            else
                fileOut << ' ';
        }
    }
    fileOut << endl;
}

void PSO::fileClose() {
    fileOut.close();
}

int myRandom(int start, int end) {
    random_device rd;
    static default_random_engine gen = default_random_engine(rd());
    uniform_int_distribution<int> dis(start, end);
    return dis(gen);
}