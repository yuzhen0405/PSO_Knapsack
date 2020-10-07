#include <iostream>
#include "PSO.h"
#include "Statistic.h"

int main() {
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < STATISTIC_ROUND; i++) {
        PSO PSO;
        PSO.run();

#if PRINT_ROUND_RESULT
        PSO.prtResult();
#endif
        statistic(PSO.getGBest());

    }
    finalResult();

    auto end = std::chrono::steady_clock::now();
    std::cout << "Time taken: " << std::chrono::duration<double>(end - start).count() << "s" << std::endl;
    return 0;
}