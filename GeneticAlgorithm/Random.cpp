#include "Random.h"

/**
 * 
 * @param min
 * @param max
 * @param gen
 * @return 
 */
double doubleRandom(double min, double max, default_random_engine *gen){    
    uniform_real_distribution<double> distributionDouble(min, max);    
    return distributionDouble(*gen);
}
/**
 * 
 * @param min
 * @param max
 * @param gen
 * @return 
 */
int intRandom(int min, int max, default_random_engine *gen){    
    uniform_int_distribution<int> distributionInt(min, max);
    return distributionInt(*gen);
}