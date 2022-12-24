#pragma once
#include <random>

//template<typename T> T random(T range_from, T range_to) {
//    std::random_device                  rand_dev;
//    std::mt19937                        generator(rand_dev());
//    std::uniform_int_distribution<T>    distr(range_from, range_to);
//    return distr(generator);
//}

template<typename T> T random(T range_from, T range_to) {
    T difference = range_from - range_to;
    T randomvalue = rand() % (int)difference;
    return (randomvalue + range_from);
}