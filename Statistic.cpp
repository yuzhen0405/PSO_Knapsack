#include "Statistic.h"
#include "PSO.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

int cntOverweight = 0; // count overweight times
int totalValue = 0;
int bestValue = 0;
int bestWeight = 0;
int bestFitness = 0;
int bestCase[10];
int cntBestCase = 0;

bool isOverweight(int w) {
    return w > KNAPSACK_SIZE;
}

// statistic of result of total rounds
void statistic(Particle gBest) {
    int w = 0, v = 0;
    for (int j = 0; j < DIMENSION; j++) {
        w += gBest.getLocation()[j] * weight[j];
        v += gBest.getLocation()[j] * value[j];
    }

    // check if it is overweight
    if (isOverweight(w)) {
        cntOverweight++;
#if DEBUG_MODE
        cout << "Overweight!!!" << endl;
#endif
    } else if (gBest.getFitness() == 620) {
        cntBestCase++;
    }

    totalValue += v;

    // check if it needs to update best fitness
    if (gBest.getFitness() > bestFitness) {
        bestWeight = w;
        bestValue = v;
        bestFitness = gBest.getFitness();
        memcpy(bestCase, gBest.getLocation(), sizeof(bestCase));
    }
}

void finalResult() {
    cout << "==================== STATISTIC ====================\n";

    cout << "Statistic Round: " << STATISTIC_ROUND << endl;
    cout << "Round: " << ROUND << endl;
    cout << "Population: " << POPULATION << endl;

    cout << setw(17) << "Overweight count" << " |"
         << setw(16) << "Overweight rate" << " |"
         << setw(17) << "Best case weight" << " |"
         << setw(11) << "Avg. value" << " |"
         << setw(11) << "Best value" << " |"
         << setw(13) << "Best fitness" << " |"
         << setw(15) << "Best case count" << endl;

    cout << setw(17) << cntOverweight << " |"
         << setw(14) << fixed << setprecision(2) << cntOverweight / (double) STATISTIC_ROUND * 100
         << setw(2) << " %" << " |"
         << setw(17) << bestWeight << " |"
         << setw(11) << setprecision(2) << totalValue / (double) STATISTIC_ROUND << " |"
         << setw(11) << bestValue << " |"
         << setw(13) << bestFitness << " |"
         << setw(15) << cntBestCase << endl;

    cout << "Best case: ";
    for (int k = 0; k < 10; k++) {
        cout << name[k] << ": " << bestCase[k] << "  ";
    }
    cout << endl;
}