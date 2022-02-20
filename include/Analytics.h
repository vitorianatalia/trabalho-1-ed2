#ifndef ANALYTICS_H_INCLUDED
#define ANALYTICS_H_INCLUDED

#include <iostream>
using namespace std;

class Analytics
{
private:
    int comparisons;
    int swaps;
    int timeInit;
    int timeEnd;
    long int inputBytes;
    long int outputBytes;

public:
    Analytics()
    {
        comparisons = 0;
        swaps = 0;
        timeInit = 0;
        timeEnd = 0;
        inputBytes = 0;
        outputBytes = 0;
    }

    ~Analytics()
    {
        comparisons = 0;
        swaps = 0;
        timeInit = 0;
        timeEnd = 0;
        inputBytes = 0;
        outputBytes = 0;
    }

    void addInputBytes(long int bytes)
    {
        inputBytes += bytes;
    }

    long int getInputBytes()
    {
        return inputBytes;
    }

    void addOutputBytes(long int bytes)
    {
        outputBytes += bytes;
    }

    long int getoutputBytes()
    {
        return outputBytes;
    }


    void addSwaps()
    {
        swaps++;
    }

    int getSwaps()
    {
        return swaps;
    }

    void addComparisons()
    {
        comparisons++;
    }

    int getComparisons()
    {
        return comparisons;
    }

    int getTimeInit()
    {
        return timeInit;
    }

    void setTimeInit(int time)
    {
        timeInit = time;
    }

    int getTimeEnd()
    {
        return timeEnd;
    }

    void setTimeEnd(int time)
    {
        timeEnd = time;
    }

    void clear()
    {
        comparisons = 0;
        swaps = 0;
        timeInit = 0;
        timeEnd = 0;
    }
};

#endif // ANALYTICS_H_INCLUDED
