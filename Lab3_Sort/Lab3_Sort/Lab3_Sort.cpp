#include <iostream>
#include <fstream>
#include <windows.h>
#include "QuickSort.h"

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

double quickSortTimerTest(int *array, int arraySize) {
    StartCounter();
    quickSort(array, array + arraySize - 1, [](int a, int b) {return a < b; });
    double elapsedTime = GetCounter();
    return elapsedTime;
}

double insertSortTimerTest(int *array, int arraySize) {
    StartCounter();
    insertSort(array, array + arraySize - 1, [](int a, int b) {return a < b; });
    double elapsedTime = GetCounter();
    return elapsedTime;
}

double combinedSortTimerTest(int *array, int arraySize) {
    StartCounter();
    combinedSort(array, array + arraySize - 1, [](int a, int b) {return a < b; });
    double elapsedTime = GetCounter();
    return elapsedTime;
}

double counterTest(char sortType, int arraySize)
{
    int array[kArraySize];
    populateIntArray(array, arraySize);
    switch (sortType) {
    case 'q':
        return quickSortTimerTest(array, arraySize);
        break;
    case 'i':
        return insertSortTimerTest(array, arraySize);
        break;
    case 'c':
        return combinedSortTimerTest(array, arraySize);
        break;
    default:
        std::cout << "Incorrect sort type!" << std::endl;
        return -1;
    }
    return 0;
}

void compareQuickInsertSorts() {
    double quickSortTime = 0.0;
    double insertSortTime = 0.0;
    const int testAmount = 100;
    std::ofstream outputFile;
    outputFile.open("compareTests.csv");
    outputFile << "arraySize,quickSort,insertSort" << std::endl;

    for (int i = 1; i < kArraySize; ++i) {
        for (int j = 0; j < testAmount; ++j) {
            quickSortTime += counterTest('q', i);
            insertSortTime += counterTest('i', i);
        }
        outputFile << i << "," << quickSortTime / testAmount << "," << insertSortTime / testAmount << std::endl;
    }
}

void compareQuickInsertCombinedSorts() {
    double quickSortTime = 0.0;
    double insertSortTime = 0.0;
    double combinedSortTime = 0.0;
    const int testAmount = 100;
    std::ofstream outputFile;
    outputFile.open("compareCombinedTests.csv");
    outputFile << "arraySize,quickSort,insertSort,combinedSort" << kInsertSortSize << std::endl;

    for (int i = 1; i < kArraySize / 8; ++i) {
        for (int j = 0; j < testAmount; ++j) {
            quickSortTime += counterTest('q', i * 8);
            insertSortTime += counterTest('i', i * 8);
            combinedSortTime += counterTest('c', i * 8);
        }
        outputFile << i * 8 << "," << quickSortTime / testAmount << "," << insertSortTime / testAmount << "," << combinedSortTime / testAmount << std::endl;
    }
}

void compareCombinedSorts() {
    double combinedSortTime = 0.0;
    const int testAmount = 100;
    std::ofstream outputFile;
    outputFile.open("compareCombinedOnlyTime.csv");
    outputFile << "arraySize,combinedSort" << kInsertSortSize << std::endl;

    for (int i = 1; i < kArraySize / 8; ++i) {
        for (int j = 0; j < testAmount; ++j) {
            combinedSortTime += counterTest('c', i * 8);
        }
        outputFile << i * 8 << "," << combinedSortTime / testAmount << std::endl;
    }
}

int main()
{
    //compareQuickInsertSorts();
    //compareQuickInsertCombinedSorts();
    //compareCombinedSorts();
    return 0;
}
