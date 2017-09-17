#ifndef RANDHELPER_H
#define RANDHELPER_H

#include <stdlib.h>

/**
 * @brief init_rand
 * @param seed
 */
void init_rand(unsigned int seed)
{
    static bool is_init = false;
    if (!is_init) {
        srand(seed);
        is_init = true;
    }
}

/**
 * @brief rrand
 * @param min
 * @param max
 * @return
 */
int rrand(int min, int max)
{
    return min + rand() % (max - min + 1);
}

/**
 * @brief brand
 * @return
 */
bool brand()
{
    return rrand(0, 1);
}

/**
 * @brief frrand
 * @param min
 * @param max
 * @return
 */
float frrand(float min, float max)
{
    return min + (rand() / (RAND_MAX / (max - min)));
}

#endif // RANDHELPER_H


