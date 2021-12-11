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

public:
    Analytics()
    {
        comparisons = 0;
        swaps = 0;
        timeInit = 0;
        timeEnd = 0;
    }

    ~Analytics()
    {
        comparisons = 0;
        swaps = 0;
        timeInit = 0;
        timeEnd = 0;
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
